import smart_thruster as thrusters
import socket,threading,os,selectors,time,math

#TODO: Interpreter Lock? Not sure if this will be an issue

HOST = '127.0.0.2'
PORT = 50008
HEADERSIZE = 5 #in bytes
MESSAGESIZE = 8*2 #in bytes
BUFSIZE = HEADERSIZE+MESSAGESIZE
RECV = 125
SEND = 255
N_motors = 8
port = '/dev/ttyS3'

MAX_RPM = 5000 #absolute maximum rpm of thrusters
EFC_RPM = 0.75*MAX_RPM #preferably dont use all of the RPM :)

zeroarr = [0 for x in range(N_motors)]

def iToC(inp):# unused
    out = [0 for x in range(size*2)]
    for i in range(size):
        out[2*i]=inp[i]>>8
        out[2*i+1]=inp[i]&0xff
    return out

def cToI(inp):# unused
    out = [0 for x in range(size)]
    for i in range(size):
        out[i]=(inp[2*i]<<8)+(inp[2*i+1])
    return out

class Data:
    def __init__(self):
        self.target_rpm=[0 for x in range(N_motors+1)] #ID values: [1,N_motors] (think set notation ;)
        self.current_rpm=[0 for x in range(N_motors+1)] #ID values: [1,N_motors]
        self.data_string=""
        self.str_length=0

    def get_tRPMs(self):
        return self.target_rpm

    def get_cRPMs(self):
        return self.current_rpm

    def set_tRPMs(self,id,val):
        self.target_rpm[id]=val

    def set_all_tRPMs(self,val):
        for id in range(n_Motors+1):
            self.target_rpm[id]=val

    def set_cRPMS(self,id,val):
        self.current_rpm[id]=val

    def set_str(self,val):
        self.data_string=val
        self.str_length=len(val)

def feedback_thread(m,d):
    while m.running:
        feedback = ""
        for id in m.motors:
            d.set_cRPMS(id,m.rpm[id])
            if(m.target_rpm[id]!=d.target_rpm[id]):
                m.target_rpm[id]=d.target_rpm[id]
            feedback += "M{0}".format(id)
            feedback += "Y" if m.is_on[id] else "N"#Y for On and N for Off.
            feedback += '{:5d}R'.format(m.rpm[id])
            feedback += '{:5.2f}A'.format(m.current[id])
            feedback += '{:5.2f}V'.format(m.voltage[id])
            feedback += '{:5.2f}C'.format(m.driver_temperature[id])
            if m.has_alarm[id]:
                print(m.get_alarm_description(id))
                print("Resetting Alarm...")
                m.reset_alarm(id)
        print()
        print(feedback.replace(" ",""))
        print(len(feedback))
        print(m.target_rpm)
        print(d.target_rpm)
        d.set_str(feedback.replace(" ",""))
        time.sleep(0.025)#Short delay. Remove this later if needed

def head(d,header): #looks at header
    if(header[0]==1&header[2]==1):
        return 0;
    if(header[4]!=MESSAGESIZE):
        print("ERROR: Data Message Size Mismatch")
        print(header)
        return -1; #-1 error code
    if(header[0]==SEND):
        return 1; #1 command received, read data
    elif(header[0]==RECV):
        return 2; #2 send received, send data ( header[1] is return message size )
    if(header[2]==RECV):
        d.set_all_tRPMs(0)
    return 0

def msg(d,arr): #looks at data array
    for i in range(int(MESSAGESIZE/2)):
        temp=(arr[2*i]<<8)+(arr[2*i+1])
        d.set_tRPMs(i+1,temp)

print("Starting Thrusters...")
m = thrusters.start(N_motors,port)
d = Data()

if(__name__=="__main__"):

    print("Feedback Thread Started")
    t1 = threading.Thread(target=feedback_thread, args=(m,d))
    t1.daemon = True
    t1.start()

    print("Main/Server Thread Started")
    while m.running:
        with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as s:
            s.bind((HOST,PORT))
            s.listen(1)
            conn, addr = s.accept()
            with conn:
                print('Connected by',addr)
                while True:
                    data = conn.recv(BUFSIZE)
                    if not data:
                        break
                    header = list(data)[:HEADERSIZE]
                    print(list(data))
                    hr = head(d,header)
                    print(hr)
                    if(hr==1): #recv instructions
                        message = list(data)[HEADERSIZE:]
                        msg(d,message)
                        print(message)
                    if(hr==2): #reply
                        print("sending: %s" % s)
                        conn.sendall(s.encode())
                    elif(hr==-1|hr==0):
                        sys.exit()

print("Closing...")
m.stop()
