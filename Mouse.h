//Initiate Mouse and Controller


int DrawCursor()
{
     if(KrnlMode==1)
     {
      float x3=((Controller.Lx-128)/32)*cursor_speed;//divide by 32 so it's not active unless its greater prevents super sensitivity :)
      float y3=((Controller.Ly-128)/32)*cursor_speed;
      cursorx+=x3;cursory+=y3;
     }
     else
     if(KrnlMode==-1)
     {
                    if(Controller.Buttons & PSP_CTRL_LEFT)cursorx-=cursor_speed+1;
                    if(Controller.Buttons & PSP_CTRL_RIGHT)cursorx+=cursor_speed+1;
                    if(Controller.Buttons & PSP_CTRL_UP)cursory-=cursor_speed+1;
                    if(Controller.Buttons & PSP_CTRL_DOWN)cursory+=cursor_speed+1;
     }
//keeps the cursor from retardedly going off the damn screen lol :) Devun_06*
if(cursorx<0)cursorx=0;
if(cursory<0)cursory=0;
if(cursorx>480)cursorx=480;//instead of implying major math here keep it
if(cursory>272)cursory= 272;//lame so it can be easy to expand upon...
draw(6,6,27,27,cursor,cursorx,cursory);
return 0;
}
