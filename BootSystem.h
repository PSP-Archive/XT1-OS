
void BootSystem()
{
SetupCallbacks();
//INIT_ALL////////////////////////////////////////////////////////////////////*
////GUI 
int Desktop=0;
int Folder=-1;
int Audio=0;
int Video=0;
int Start=-1;
int Message=0;
int KrnlMode=-1;
int DesktopFeatures;
//////////////////
struct Program
{
       int x;
       int y;
}program;
////Cursor
typedef struct Cursor
{
       int x;
       int y;
       float speed;
}cursor;
//////////////////
struct File
{
       int hrz;
       int vrt;
}file;
//////////////////
struct Menu
{
       int list0;
       int list1;
       int list2;
       int list3;
       int list4;
}menu;
/////////////Call Various System Variables
SceUID openfile;
char data0[200];
char data1[200];
////////PULL MOUSE NOW///////*
SceCtrlData Controller;
sceCtrlSetSamplingCycle(0);
sceCtrlSetSamplingMode(0);
int LastButton;
/////////////////////////*
char usertheme[15];
char username[20];
//USERNAME
openfile = sceIoOpen("ms0:/KXP-OS/System/Structure/UserName", PSP_O_RDONLY|PSP_O_CREAT,0);
sceIoRead(openfile,username,20);
sceIoClose (openfile);
//USERTHEME
openfile = sceIoOpen("ms0:/KXP-OS/System/Structure/UserName", PSP_O_RDONLY|PSP_O_CREAT,0);
sceIoRead(openfile,usertheme,15);
sceIoClose (openfile);
//**************************System - Graphics**********************************/
char graphics[200];
    Image*startbar;
    Image*topmenu;
    Image*mainscreen;
    Image*cursor;
    Image*button0;
    Image*button1;
    Image*strt0;
    Image*strt1;
    Image*strt2;
    Image*bdead;
    Image*bvlow;
    Image*bmlow;
    Image*bhigh;
    Image*bchrg;
    Image*bgpic;

//LOAD MAIN PORTIONS OF OPERATING SYSTEM.
    sprintf(graphics,"ms0:/KXP-OS/System/Resources/Themes/%s/MainFrames/Bottom.png",usertheme);
    startbar=insertpx(graphics);
    sprintf(graphics,"ms0:/KXP-OS/System/Resources/Themes/%s/MainFrames/Top.png",usertheme);
    topmenu=insertpx(graphics);
    sprintf(graphics,"ms0:/KXP-OS/System/Resources/Themes/%s/MainFrames/Scr0.png",usertheme);
    mainscreen=insertpx(graphics);
    //SYSTEM DIRECTORY BELOW -->
    openfile = sceIoOpen ("ms0:/KXP-OS/System/Structure/Wallpaper", PSP_O_RDONLY|PSP_O_CREAT,0);
    sceIoRead(openfile,graphics,20);
    sceIoClose(openfile);
    sprintf(graphics,"ms0:/KXP-OS/System/Resources/Wallpaper/%s",graphics);
    bgpic=insertpx(graphics);
    //LOAD SYSTEM PORTION OF OPERATING SYSTEM.
    sprintf(graphics,"ms0:/KXP-OS/System/Resources/Themes/%s/SystsemIcons/Cursor.png",usertheme);
    cursor=insertpx(graphics);
    sprintf(graphics,"ms0:/KXP-OS/System/Resources/Themes/%s/SystsemIcons/B0.png",usertheme);
    button0=insertpx(graphics);
    sprintf(graphics,"ms0:/KXP-OS/System/Resources/Themes/%s/SystsemIcons/B1.png",usertheme);
    button1=insertpx(graphics);
    //LOAD START PORTION OF OPERATING SYSTEM.
    sprintf(graphics,"ms0:/KXP-OS/System/Resources/Themes/%s/Start/S0.png",usertheme);
    strt0=insertpx(graphics);
    sprintf(graphics,"ms0:/KXP-OS/System/Resources/Themes/%s/Start/S1.png",usertheme);
    strt1=insertpx(graphics);
    sprintf(graphics,"ms0:/KXP-OS/System/Resources/Themes/%s/Start/S2.png",usertheme);
    strt2=insertpx(graphics);
    //LOAD BATTERY PORTION OF OPERATING SYSTEM.
    sprintf(graphics,"ms0:/KXP-OS/System/Resources/Themes/%s/Battery/0.png",usertheme);//DEAD//
    bdead=insertpx(graphics);
    sprintf(graphics,"ms0:/KXP-OS/System/Resources/Themes/%s/Battery/1.png",usertheme);//VERY LOW//
    bvlow=insertpx(graphics);
    sprintf(graphics,"ms0:/KXP-OS/System/Resources/Themes/%s/Battery/2.png",usertheme);//MODERATELY LOW//
    bmlow=insertpx(graphics);
    sprintf(graphics,"ms0:/KXP-OS/System/Resources/Themes/%s/Battery/3.png",usertheme);//HIGH//
    bhigh=insertpx(graphics);
    sprintf(graphics,"ms0:/KXP-OS/System/Resources/Themes/%s/Battery/4.png",usertheme);//CURRENTLY CHARGING//
    bchrg=insertpx(graphics);
    //FINISH ADDING LOADS LATER...
//////////////////////
//**************************System Functions**********************************/
void FixControllerMode()
{
if(KrnlMode==1) sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
                else
if(KrnlMode==-1) sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);
}
//////////////////////


void DrawDesktop()
{
    draw(0,0,480,18,startbar,0,272-18);
    draw(0,0,84,18,strt0,0,272-18);
    print(0,0,"KXP-OS : by Devun_06 shouts out to my boys James>M.M.M.>Kyle",rgb(0,0,168));
    print(0,10,"...and all my other friends :)",rgb(0,0,168));
}
//////////////////////


void DrawBattery()
{
    if(scePowerIsBatteryExist())
    {
    if(scePowerGetBatteryLifePercent()<75)draw(0,0,23,18,bmlow,480-66,272-18);
                                else
    if(scePowerGetBatteryLifePercent()<50)draw(0,0,23,18,bvlow,480-66,272-18);
                                else
    if(scePowerGetBatteryLifePercent()<25)draw(0,0,23,18,bdead,480-66,272-18);
                                else 
                                draw(0,0,23,18,bhigh,480-66,272-18);
    }else{draw(0,0,23,18,bchrg,480-66,272-18);}
}
//////////////////////


void DrawTime()
{
    struct tm *TimeNow;
    time_t psclock;
    sceKernelLibcTime(&psclock);
    TimeNow = localtime(&psclock);
    sceKernelLibcTime(&psclock);//used &psptime so it can let sceKernelLibcTime set it to the 1970 epoch time in seconds.
    strftime(data0,20,"%H:%M",TimeNow);
    print(443,272-11,data0,rgb(0,0,255));
}
//////////////////////


void DrawCursor()
{
     if(KrnlMode==1)
     {
//divide by 32 so it's not active unless its greater prevents super sensitivity :)
      cursor.x+=((Controller.Lx-128)/32)*cursor.speed;
      cursor.y+=((Controller.Ly-128)/32)*cursor.speed;;
     }
     else
     if(KrnlMode==-1)
     {
                    if(Controller.Buttons & PSP_CTRL_LEFT)cursor.x-=cursor.speed+1;
                    if(Controller.Buttons & PSP_CTRL_RIGHT)cursor.x+=cursor.speed+1;
                    if(Controller.Buttons & PSP_CTRL_UP)cursor.y-=cursor.speed+1;
                    if(Controller.Buttons & PSP_CTRL_DOWN)cursor.y+=cursor.speed+1;
     }
//keeps the cursor from retardedly going off the damn screen lol :) Devun_06*
if(cursor.x<0)cursor.x=0;
if(cursor.y<0)cursor.y=0;
if(cursor.x>480)cursor.x=480;//instead of implying major math here keep it
if(cursor.y>272)cursor.y= 272;//lame so it can be easy to expand upon...
draw(6,6,27,27,cursor,cursor.x,cursor.y);
}
//////////////////////
}//end of BootSystem!
