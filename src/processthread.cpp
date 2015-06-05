#include "processthread.h"

processThread::processThread(QObject *parent) :
    QThread(parent)
{
    mode = 0;
    ctl1 = 0;
    ctl2 = 0;
    springPitch = true;
    springMod = false;
    spring1 = false;
    spring2 = false;
    rel = false;
    xtype = 1;
    ytype = 2;
    ztype = 0;
    xctl = 1;
    yctl = 2;
    zctl = 3;
    notelow = 48;
    notehigh = 84;
    stop = false;

    midicontrol.initMidi();
    initsynclient(&xmin,&xmax,&ymin,&ymax,&zmin,&zmax);
    touchpad = shm_init();

}

void processThread::run()
{
    SynapticsSHM old, cpy;
    int xspan = xmax-xmin;
    int yspan = ymax-ymin;
    int zspan = zmax-zmin;
    int xpitch = xmin;
    int xmod   = xmin + xspan/4;
    int xctl1 = xmin + 2*xspan/4;
    int xctl2 = xmin + 3*xspan/4;
    int p = 0, m = 0, c1 = 0, c2 = 0;
    int val, lastp = 0, lastm = 0, lastc1 = 0, lastc2 = 0;
    int firstp = 0, firstm = 0, firstc1 = 0, firstc2 = 0;
    double x, y, z;
    int velocity, note, noteon=0;

    if (!touchpad){
        printf("ERROR connecting to touchpad!");
        return;
    }
    old.fingerWidth = 1;
    old.x = 0;
    while (!stop){
        cpy = *touchpad;
        if (!is_equal(&old,&cpy)){
            try{
                if (mode == 0){//ctl wheel
                    if ((cpy.z > zmin)&&(old.z > zmin)){//zmin is a threshold to prevent false touches
                        y = int((cpy.y+old.y)/2);
                        val = (ymax - y)*127/yspan;
                        if (val>127)val=127;
                        if (val<0)val=0;
                        if (cpy.x > xctl2){
                            if (firstc2 == 0)
                                firstc2 = val;
                            if (rel)
                                val = val - firstc2 + lastc2;
                            midicontrol.sendController(ctl2,val);
                            emit ctl2Changed(val);
                            c2 = val;
                        }else if (cpy.x > xctl1){
                            if (firstc1 == 0)
                                firstc1 = val;
                            if (rel)
                                val = val - firstc1 + lastc1;
                            midicontrol.sendController(ctl1,val);
                            emit ctl1Changed(val);
                            c1 = val;
                        }else if (cpy.x > xmod){
                            if (firstm == 0)
                                firstm = val;
                            if (rel)
                                val = val - firstm + lastm;
                            midicontrol.sendController(1,val);
                            emit modChanged(val);
                            m = val;
                        }else if (cpy.x >= xpitch){
                            val = val*2*8191/127 - 8191;
                            if (firstp == 0)
                                firstp = val;
                            if (rel)
                                val = val - firstp + lastp;
                            midicontrol.sendBender(val);
                            emit pitchChanged(val);
                            p = val;
                        }
                    }else{//not touching
                        if (rel && p+m+c1+c2)
                        {
                            firstp = firstm = firstc1 = firstc2 = 0;
                            lastp = p;
                            lastm = m;
                            lastc1 = c1;
                            lastc2 = c2;
                        }
                        if(springPitch && p){
                            midicontrol.sendBender(0);
                            emit pitchChanged(0);
                            p = lastp = 0;
                        }
                        if(springMod && m){
                            midicontrol.sendController(1,0);
                            emit modChanged(0);
                            m = lastm = 0;
                        }
                        if(spring1 && c1){
                            midicontrol.sendController(ctl1,0);
                            emit ctl1Changed(0);
                            c1 = lastc1 = 0;
                        }
                        if(spring2 && c2){
                            midicontrol.sendController(ctl2,0);
                            emit ctl2Changed(0);
                            c2 = lastc2 = 0;
                        }
                    }
                }else{//xytable
                    if ((cpy.z > zmin)&&(old.z > zmin)){
                        x = double((cpy.x+old.x)/2 - xmin)/xspan;
                        y = double(ymax - (cpy.y+old.y)/2)/yspan;
                        z = double((cpy.z+old.z)/2 - zmin)/zspan;
                        if (x>1)x=1;if (x<0)x=0;
                        if (y>1)y=1;if (y<0)y=0;
                        if (z>1)z=1;if (z<0)z=0;

                        if (xtype == 1){//note
                            note = int((x)*(notehigh-notelow)+notelow);
                            emit Xchanged(note);
                        }else if (ytype == 1){
                            note = int((y)*(notehigh-notelow)+notelow);
                            emit Ychanged(note);
                        }else if (ztype == 1){
                            note = int((z)*(notehigh-notelow)+notelow);
                            emit Zchanged(note);
                        }else note = 0;

                        if (xtype == 2){//velocity
                            velocity = x*127;
                            emit Xchanged(velocity);
                        }else if (ytype == 2){
                            velocity = y*127;
                            emit Ychanged(velocity);
                        }else if (ztype == 2){
                            velocity = z*127;
                            emit Zchanged(velocity);
                        }else velocity = 115;

                        if (xtype == 3){//ctl
                            midicontrol.sendController(xctl,x*127);
                            emit Xchanged(int(x*127));
                        }
                        if (ytype == 3){
                            midicontrol.sendController(yctl,y*127);
                            emit Ychanged(int(y*127));
                        }
                        if (ztype ==3){
                            midicontrol.sendController(zctl,z*127);
                            emit Zchanged(int(z*127));
                        }

                        if (noteon != note){
                            midicontrol.sendNoteOff(noteon);
                            noteon = note;
                            if (note)
                                midicontrol.sendNoteOn(note,velocity);
                        }

                    }else{//not touching
                        if (noteon){
                            midicontrol.sendNoteOff(noteon);
                            noteon = 0;
                            emit Xchanged(0);
                            emit Ychanged(0);
                            emit Zchanged(0);
                        }
                    }
                }
                old = cpy;
            }catch(RtError&){
                printf("error in sending control signals\n");
            }
        }
        usleep(50000);//can change the sampling time if you like
    }



}
