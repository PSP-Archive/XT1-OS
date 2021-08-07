#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <pspctrl.h>
#include <pspgu.h>
#include <png.h>
#include "graphics.h"
#include <pspiofilemgr.h>
#include <dirent.h>
#include <psppower.h>
#include <pspaudio.h>
#include <psploadexec.h>
#include <pspaudiolib.h>
//#include <pspsdk.h>
#include "mp3player.h"
//#include "oggplayer.h"
#include "Exits.h"
#include "time.h"
#include "screenshot.h"
#include <pspumd.h>
#define print printTextScreen
#define DisableGraphics disableGraphics
#define insertpx loadImage
#define dprint pspDebugScreenPrintf
#define clearDebug pspDebugScreenClear
#define draw blitAlphaImageToScreen
#define rgb(R, G, B) ((R)|((G)<<8)|((B)<<16))
//WELCOME TO THE INSIDE OF DVN OS...
//DVN OS IS AN OPERATING SYSTEM SOLELY FOR THE PLAYSTATION PORTABLE AKA:PSP
//THE STRUCTURE OF DVN OS IS EVIDENCE OF A SURE TIGHT SOURCE CODE
//BUILT MAINLY IN HOPES OF USING LESS M.DUO SPACE WHILE KEEPING THE SOURCE
//EASY TO MAINTAIN, READ, EXPAND, AND UNDERSTAND.
//THE SYSTEM IS HOPED TO BE IN THE FUTURE AN OUTSTANDING OPERATING SYSTEM BUILT
//ALMOST ENTIRELY UNDER ARRAYS FOR AN EVEN SLIGHTER WHAT THEY CALL "UMPH".
//FEEL FREE TO OBSERVE, STUDY, OR DO W/E IT IS YOU WISH TO DO WITH THIS CODE...
// THAT IS IF YOU OBTAINED ACCESS TO IT PROPERLLY AND WITH THE LEGAL
//AUTHOR(S) PERMISSION. :)
/*
||||||||||||||||\                    /\
||||             \                  / \
||||              \                /  \
||||               |              /   \
||||               |\            /    \
||||               | \          /     \
||||               |  \        /      \
||||               |   \      /       \
||||              /     \    /        \
||||             /       \  /         \
||||||||||||||||/         \/          \*/
//SCREW THAT DESIGN CRAP... THAT TOOK TOO LONG. I DON'T KNOW HOW ALL THOSE OTHER PEOPLE BE DOING THAT... I'D HAVE TO BE SUPER BORED.
//I KINDA SEE AN 'N' BUT I DON'T KNOW... HMMM.
PSP_MODULE_INFO("XT1-OS",0,1,1);
int main()
{
    void halt(unsigned int pause)
    {
    unsigned int pause2;
    for (pause2=0; pause2<=pause; pause2++) sceDisplayWaitVblankStart();
    }
////////////////////NOW WORKING ON:IF SOMETHING GOES WRONG NEAR THE MAX AMOUNT OF WIDOWS, CHECK THE PREPARE DEPTH ? FIXING DYNAMIC DEPTH WINDOWING ? inputing depth changing like when opening a window d.depth++; :) ? NEED TO PLACE ALL CARRY WINDOW FUNCTION CALLS BEFORE THE DRAWINGS APPLIED TO THEM... MAKES THE CARRY FIRST SO IT GOES A LITTLE SMOOTHER.
SceCtrlData Controller;
SceCtrlLatch Force;
SetupCallbacks();
pspDebugScreenInit();
pspAudioInit();
//OGG_Init(1);
MP3_Init(1);
pspDebugScreenSetTextColor(rgb(255,0,0));
dprint("Please be patient while XT1-OS loads...");halt(9);
//INIT_ALL////////////////////////////////////////////////////////////////////*
//dprint("\n\n");for(pause=0; pause<53; pause++)sceDisplayWaitVblankStart();
//////////////////////////////////////////////////////////////////////////////*
clearDebug();
pspDebugScreenSetTextColor(rgb(0,210,0));
dprint("Loading Gui Variables...");halt(9);
////GUI 
int Desktop=1;
int Folder=-1;
int DesktopIcons=1;
char Directory[141];
char DirectoryAdd[210];
int Start=-1;
char File[350];
char FileAdd[210];
char FileHold[350];
char ProgramsRunning[8][100];//zero aint supposed to be used:
int ProgramsRunningC=-1;
int ProgramActive=0;//works through the above programsrunning
///////////SETTINGS//////////////
int sttpower=-1;
int RepairLag=-1;
int Standby=-1;
int StopPowerSave=-1;
int ClipMusicExt=-1;
int ClipImageExt=-1;
int ClipPaperExt=-1;
int ClipCodesExt=-1;
int ClipFLnk9Ext=-1;
//AMERICAN REGION SETUP//
int ControllerRegion=-1;//-1 == AMERICAN X=LEFT; O=RIGHT 1=JAPANESE 0=LEFT X=RIGHT
int FIRSTCLICK=PSP_CTRL_CROSS;
int SECONDCLICK=PSP_CTRL_CIRCLE;
int FIRSTCLICKREADY=1;
int SECONDCLICKREADY=1;
int STARTPRESSREADY=1;
/////////////////////////////////
//******* COLOR COLLECTIONS
//HEX IS ACCEPTED VALUES FROM 0-F
//int PrimaryClr;//text,message, box... time text and battery text etc...
//int SecondaryClr;//misc like... audio bottom title, startmenu next-> maybe for txt scroll data show etc...
//int TitleClr;//back*, msgbox title, directory prints,etc... Month & Battery titles too
//int TimeClr;//color for time viewed on desktop
//int MainClr;//start menu etc...
//int SelctClr;//messagebox buttons etc...
//int WarningClr;//color for important messages and warnings... 
//int DirClr;//used for files and folders name prints...
//*******PREPARE COLOR COLLECTIONS
//fillllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll
int KrnlMode=-1;
int DesktopFeatures;
char DesktopFeaturesData0[100];
char DesktopFeaturesData1[100];
char DesktopFeaturesData2[100];
char DesktopFeaturesData3[100];
char DesktopFeaturesData4[100];
char DesktopFeaturesData5[100];
float DesktopFeaturesData6;
int DesktopFeaturesData7;
char time[20];
int counter;
/*for(ActiveWindowCount=0; ActiveWindowCount<=2; ActiveWindowCount++)
{
//if(ActiveWindow[ActiveWindowCount]==2)DrawNotePad();
//if(ActiveWindow[ActiveWindowCount]==1)DrawVideo();
if(ActiveWindow[ActiveWindowCount]==0)DrawAudio();
}*/
//////////////////

//Start Menu
DIR             *StartDirectory;
struct dirent   *drt;
struct SystemColorss
{
       char dir[388];
       char conversion_unit[10];//would have set to 9, but there was a buffer overflow I believe reason why if I did it broke :(
       char system[8][14];//this would have been 17 instead of 80, but... buffer overflow ;)// nvm the biggest 0-12 so 13=\0 and we have just compacted our buffer :p
       //strncpy & memcpy requires the buffer to be 1 larger than necessary making because they cannot overlap it said <=> rgb[4]
       char red[8][4];//has to be 4
       char grn[8][4];//has to be 4
       char blu[8][4];//0-7<-//has to be 4
       int count;
}clr;
sprintf(clr.system[0],"Primary_Clr");////*<
sprintf(clr.system[1],"Main_Clr");///////*<
sprintf(clr.system[2],"Secondary_Clr");//biggest one: has 13 characters :0(*not counting zero)
sprintf(clr.system[3],"Title_Clr");//////*<
sprintf(clr.system[4],"Dir_Clr");////////*<
sprintf(clr.system[5],"Time_Clr");///////*<
sprintf(clr.system[6],"Warning_Clr");////*<
sprintf(clr.system[7],"Selct_Clr");//////*<
struct Starts
{
       //16 because it's 17 item slots in the start menu including "0" so add +1
       char item[17][210];
       char dis_item[17][210];//same as item, but doesn'y hold exact fullname for easy of directory use but is used for display so can be changed best for appearances :D
       int type[17];//0 folder //1 file //2 next 0 WILL NOT BE USED HERE IT CAUSES ERRORS *SEE BELOW
       //OKAY, I FOUND AN ERROR AND NOTHING IN MY CODE WAS WRONG BUT THE TYPE 0 AND 1 WOULD BE WAAAAAY OFF. NEXT, I REALIZED THAT IT
       //WAS SIMILIAR TO THE PROBLEM WITH ITEM NAMES... WHEN ONE IS TOO BIG IT WOULD WRITE THE REST OF ITSELF TO THE NEXT NOW I FIGURE
       //THAT WAS THE PROBLEM BECAUSE TYPE[0] IS THE SAME AS TYPE SO INSTEAD OF WRITING TO TYPE[0] IT WROTE TO TYPE... :) FILLING ALL SPACES
       //AVAILABLE. :)
       int current_page;//current page being viewed.
       //int move_pages;//move to this page
       int page_check;
       int page_should_be;
       int more_pages_exists;// 0 and 1 if there is another page :p I'm soooo stubborn sorry^
       char title[220];//THIS DOESN'T NEED TO BE THIS BIG. SET TO 10 WHEN RELEASING
       char itemhold[210];
       int typehold;
       int counter;// 1 or zero if next category exists... if it does then in other calls will look like if(start.more_pages_exists=1){start.move_pages++;)
}start;start.typehold=-1;start.current_page=0;

//Program Column collector//*
int P_Column;             //*
///////////////////////////\*
struct AMedia//Audio Structure
{
       int show;
       int play;
       int pause;
       int back;
       int forward;
       int style;//0none,1shuffle,2next,3loop
       int x;
       int y;
       int mp3list[20][210];//holds a list for cycle back etc...
       int isplaying;
       char currently_playingpth[350];//includes path
       char currently_playing[210];//includes no path
       char dis_currently_playing[210];//displayed view of currently playing :)
       char last[210];
       int size;//compaq or large compaq = 0;
       int carryx;
       int carryy;
       int char_switch;
       int current_char;
       int carry;//if it carries or not for dragging
       int count;
       int lagspace;
       int type;
       int resume_later;
       int ProgramsRunningC;
}aud;aud.size=-1;aud.style=0;aud.ProgramsRunningC=-1;aud.char_switch=0;aud.current_char=0;aud.resume_later=0;
aud.lagspace=0;
sprintf(aud.dis_currently_playing,"Song: ");
aud.dis_currently_playing[17]='\0';///\****************************************\/^//cuts off letters above 10 shows 0-10 :) that's 10 not including "Song: "
//read file for x,y,size and style;
void EndAMedia()
{
     //write file boot info to text like x,y,shade, style, and size;
     aud.play=0;
     aud.pause=0;
     aud.isplaying=0;
     aud.back=0;
     aud.forward=0;
     aud.show=-1;
     aud.resume_later=0;
}
//icons are 36x36

struct VMedia//Video Structure
{
       int show;
       int play;
       int pause;
       int back;
       int forward;
       int x;
       int y;
       int shade;//let user put see through shades they made themselves over the movie for color changing 2 for compaq and 2 for fullscreen
       int fullscreen;//compaq or fullscreen compaq = 0;
       int style;//0none,1shuffle,2next,3loop
       int carryx;
       int carryy;
       int carry;
}vid;vid.fullscreen=-1;
//read file for x,y,shade,fullscreen, and style;
void EndVMedia()
{
     //write file boot info to text like x,y,shade, style, and fullscreen;
     vid.play=0;
     vid.pause=0;
     vid.back=0;
     vid.forward=0;
     vid.show=-1;
}
struct Notepad//Text Viewing Structure
{
       int id[6];
       int show[6];
       int rows[6];//in other words... how many lines;
       int columns[6];//how many character across;
       int x[6];
       int y[6];
       int fullscreen[6];
       int scroll[6];
       int carryx;
       int carryy;
       char lines[87][61];//17*5 actually should only use 85, but integers require an extra to prevent buffer overflow ;) and I added +1 because the math script required me to so... it's now 87
       int size_in_bytes[6];
       int carry[6];
       char file[6][350];
       int active;
       int count;
       int counter;
       int depth[6];
       int number_of_usable_windows;//will = 5 because 0-4 are active and usable ;)
       int ProgramsRunningC;
}txt;txt.active=-1;txt.ProgramsRunningC=-1;txt.number_of_usable_windows=5;
for(txt.count=0; txt.count<6; txt.count++){txt.depth[txt.count]=-1;txt.x[txt.count]=16*5;txt.y[txt.count]=lround(16*(((272-208)/16)/2));txt.scroll[txt.count]=0;txt.show[txt.count]=0;txt.fullscreen[txt.count]=-1;txt.carry[txt.count]=0;}
//if no notepad besides 1 has been opened, when closing, it will try to move the next to the original active, but will crash, I'm guessing cause the others would have no strings applied yet
for(txt.count=0; txt.count<87; txt.count++){txt.lines[txt.count][0]='\0';}
//*************************************

//*************************************
//read file for x,y,rows,and columns;
void EndNotepad()
{
     //write file boot info to text like x,y,rows, and columns;
     txt.scroll[txt.active]=0;
     txt.show[txt.active]=0;
}
struct MessageWindow
{
     int x;
     int y;
     int bx;// this is the x to the first button you don't need the other button's x... just push a little math :P
     int by;// this is the same for button 2
     int type;
     char message[100];
     char title[50];
     int bttntext0;//x value
     int bttntext1;//x value
     int bttntexty;
     char btext0[10];
     char btext1[10];
     int tcenter0;
     int tcenter1;
     int carry;
     int carryx;
     int carryy;
}msg;msg.x=240-112;msg.y=127-48;msg.carry=0;
struct WindowHandling
{
       int carry_count;
       int draw_count;
}wh;
struct Iconss
{
       int x;//width of icon pic
       int y;//height of the icon pic
       int spacex;//the x spacing between icon pics when in folders~
       int spacey;// the y spacing between icon pics when in folders~
       int splitx;//division number of icon width
       int splity;//division number of icon height
       int smallspacex;
       int smallspacey;
       int round;
}ico;
//since ico.x will be user set for true themes, we add this check.
ico.x=48;ico.y=48;
if(ico.x<1||ico.y<1){DisableGraphics();
while(1){clearDebug();dprint("(error) source: Either the width and/or height of the selected theme's icon attributes have an invalid value <1.");}}
ico.splitx=4;ico.splity=4;ico.spacex=ico.x/ico.splitx;ico.spacey=ico.y/ico.splity;
//if(cursor.x/12==cursor.x/48)<==>if(cursor.x/ico.spacex==cursor.x/ico.x){} OR cursor.x/ico.spacex!=(cursor.x/ico.x)*4 )OR cursor.x/((ico.spacex*(ico.splitx+1))*(cursor.x/ico.x))!=1 OR (cursor.x-(ico.spacex+(ico.spacex*0)))/ico.x==0
//to center we find how much room is left and we divide it by what is being used and add it to the x's spacing :)
//OBTAIN FIXED LINING****\//
//X-X-X
ico.spacex=ico.spacex+(((480)%(ico.x+ico.spacex))/((480)/(ico.x+ico.spacex)));
//Y-Y-Y
ico.spacey=ico.spacex+(((272)%(ico.y+ico.spacey))/((272)/(ico.y+ico.spacey)));
/*
//CENTER SPACE VALUE*****\//
//set smallspacex for centering
//304 == compact folder pic width.// 304 was the original width of the folders during creation of this program so it's now replaced with thm.folder_width for theme purposes ;)
//SETUP ALL "X" VALUES
ico.round=thm.folder_width/ico.x;//int can't hold decimal places, so we get cleaned here ;)
// if round is not cleaned, the floating point is evaluated in the formula!!
ico.smallspacex=(thm.folder_width-(ico.x*ico.round)) / (ico.round);//(304%ico.x) should == 16 but it's ruined because for / we receive 6.3333-> so 
//\************************************************
ico.spacex=ico.spacex-(ico.spacex/(480/(ico.x+(ico.x/ico.splitx))));//(ico.x/ico.splitx)==spacex
//SETUP ALL "Y" VALUES
//(thm.folder_height-(thm.menu_height*2)) this equal folder width without counting menus
ico.round=(thm.folder_height-(thm.menu_height*2))/ico.y;
ico.smallspacey=((thm.folder_height-(thm.menu_height*2))-(ico.y*ico.round)) / (ico.round);
ico.spacey=ico.spacey-(ico.spacey/(272/(ico.y+(ico.y/ico.splity))));//(ico.y/ico.splity)==spacey
//ico.smallspacey=0;
*/
struct FolderWindow
{
       //33 cause 32 files exists in folders at MAX
       //6 cause 5 windows at MAX ;)
       int show[6];
       int x[6];
       int y[6];
       int selection[6];
       //166 because 33*5 == 165 need 1 extra or buffer overflow happens
       char file[166][210];//0-32=active(1);33-65=active(2); etc... ;)
       //actual string displayed :) fld2 -->
       int current_page[6];
       int page_should_be[6];
       int more_pages_exists[6];
       char filehold[6][210];
       int type[166];
       //int move_pages[6];
       int typehold[6];
       int max[6];
       int carryx;
       int carryy;
       int carry[6];
       int fullscreen[6];
       char dir[6][200];
       int counter;
       int active;
       int file_count;
       int column;
       char *extension;
       int format[166];
       int start;
       int number_of_usable_windows;//will = 5 because 0-4 are active and usable ;)
       int ProgramsRunningC;
       int depth[6];
}fld;fld.active=-1;fld.ProgramsRunningC=-1;fld.start=0;fld.number_of_usable_windows=5;
for(fld.counter=0; fld.counter<6; fld.counter++)
{fld.show[fld.counter]=0;fld.depth[fld.counter]=-1;fld.carry[fld.counter]=0;fld.current_page[fld.counter]=0;fld.page_should_be[fld.counter]=0;fld.fullscreen[fld.counter]=0;}
//Folder Window originally implemented within itself the display text variable array, but has it removed now for the sake of the stack size
struct FolderWindow2//created for prevention of stack overflow
{
//actual string displayed :)
       char dis_dir[6][200];
       char dis_file[166][210];
}fld2;
struct Depth
{
       int depth;
       int count;
       int counter;
       int max;
}d;d.depth=-1;d.max=txt.number_of_usable_windows+fld.number_of_usable_windows;
struct SystemDirectories
{
       char file[33][210];
       int more_pages_exists;
       int current_page;
       int page_should_be;
       char dis_file[33][210];
       char filehold[210];
       int typehold;
       char dir[350];
       int counter;
       int type[33];
       int column;
       int format[33];//used to check what icon is drawn;
       int category;//1==skins... 2==wallpaper~
}sd;sd.current_page=0;
struct ExternalLinks
{
char pdf_view[210];
char paint_edit[210];
}EXTRN;
//set these to read from files in struct for program to be called when files relative to these topics are selected...
struct Themesss
{
//SYSTEM
 int font_width;
 int font_height;
 int menu_width;
 int menu_height;
 int fullscreen_width;
 int fullscreen_height;
 int folder_width;
 int folder_height;
 int startbar_height;
 int battery_width;
 int battery_height;
 int time_width;
 int time_height;
 int files_width;
 int files_height;
 int startbutton_width;
 int startbutton_height;
 int startmenu_height;
 int startmenu_width;
 int startboard_width;
 int startboard_height;
 int startitem_width;
 int startitem_height;
 int cursor_height;
 int cursor_width;
 //TEXT
 int twindow_width;
 int twindow_height;
 //MESSAGE BOX
 int msgbox_width;
 int msgbox_height;
 int msgboxbtn_width;
 int msgboxbtn_height;
 //MEDIA PLAYER
 int mtopbar_height;
 int mtopbar_width;
 int mwindow_width;
 int mwindow_height;
 int mbutton_width;
 int mbutton_height;
}thm;
//////////////////////
//MESSAGE INITIATOR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitMessage(char *msgtitle, char *msgdialog, char *msgbutton0, char *msgbutton1, int msgtype)
{
     sprintf(msg.title,"%s",msgtitle);
     sprintf(msg.message,"%s",msgdialog);
     if(msgtype==1 || msgtype==2)msg.type=msgtype;else msg.type=1;
     if(msgtype==1)msg.bx=msg.x+((224/2)-(80/2));
     if(msgtype==2)msg.bx=msg.x+(thm.menu_width*1);
     msg.by=(msg.y+(thm.menu_height*4))+8;
     msg.tcenter0=lround(((strlen(msgbutton0)-1)*8)/2);//-1 to ignore '\0'
     msg.tcenter1=lround(((strlen(msgbutton1)-1)*8)/2);//-1 to ignore'\0' & because 8 is how wide and tall the letters are I think i saw 8 somewhere in the image.h or w/e :)
     msg.bttntext0=(msg.bx+40)-msg.tcenter0;
     msg.bttntext1=(((msg.bx+80)+(thm.menu_width*2))+40)-msg.tcenter1;
     msg.bttntexty=msg.by+3;
     sprintf(msg.btext0,"%s",msgbutton0);
     sprintf(msg.btext1,"%s",msgbutton1);
}//How to Call://InitMessage("System","Please understand, not all homebrews are correctly launced from the OS. Would you like to continue?","Yes","No",2);
///How to Show://if ((DisplayMsgbox())==1){Launch Homebrew;}else{Don't Launch Homebrew;}//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Clip_Extension(int NameLength,char* SurFileName)
{
    char *rip; rip=strrchr(SurFileName,'.');
    if(rip==NULL   ||   ( NameLength <= strlen(SurFileName)-strlen(rip) )) return NameLength;
    else
    {//if needed ;)
    
    //******************\//MUSIC
    if(ClipMusicExt==1)
    {
    if(stricmp(rip,".mp3")==0||
    stricmp(rip,".ogg")==0||
    stricmp(rip,".wav")==0||
    stricmp(rip,".mid")==0)
    {rip[0]='\0'; return NameLength-(strlen(rip)-(strlen(SurFileName)-NameLength));}
    }
    
    //else
    
    //******************\//TEXT
    if(ClipPaperExt==1)
    {
    if(stricmp(rip,".txt")==0||stricmp(rip,".doc")==0||stricmp(rip,".html")==0||
    stricmp(rip,".wri")==0||stricmp(rip,".rtf")==0||stricmp(rip,".log")==0||
    stricmp(rip,".vbs")==0||stricmp(rip,".c")==0||stricmp(rip,".c++")==0||
    stricmp(rip,".ini")==0)
    {rip[0]='\0'; return NameLength-(strlen(rip)-(strlen(SurFileName)-NameLength));}
    }
    
    //else
    
    //******************\//PICTURES
    if(ClipImageExt==1)
    {
    if(stricmp(rip,".jpg")==0||
    stricmp(rip,".jpeg")==0||stricmp(rip,".png")==0||
    stricmp(rip,".gif")==0||stricmp(rip,".tiff")==0||
    stricmp(rip,".jpe")==0||stricmp(rip,".ico")==0||
    stricmp(rip,".bmp")==0||stricmp(rip,".pbm")==0||
    stricmp(rip,".pdd")==0||stricmp(rip,".tga")==0||
    stricmp(rip,".pcd")==0||stricmp(rip,".pic")==0||
    stricmp(rip,".jfif")==0||stricmp(rip,".pcx")==0||
    stricmp(rip,".fax")==0||stricmp(rip,".icb")==0||
    stricmp(rip,".win")==0||stricmp(rip,".scr")==0||
    stricmp(rip,".vda")==0||stricmp(rip,".emf")==0||
    stricmp(rip,".psp")==0)
    {rip[0]='\0'; return NameLength-(strlen(rip)-(strlen(SurFileName)-NameLength));}
    }
    
    //else
    
    //******************\//FASTLINK9S
    if(ClipFLnk9Ext==1)
    {
    if(stricmp(rip,".fl9")==0)
    {rip[0]='\0'; return NameLength-(strlen(rip)-(strlen(SurFileName)-NameLength));}
    }
    
    //else
    
    //******************\//SCRIPTS & EXECUTABLES
    if(ClipCodesExt==1)
    {
    if(stricmp(rip,".script")==0||
    stricmp(rip,".lua")==0||
    stricmp(rip,".elf")==0||
    stricmp(rip,".prx")==0||
    stricmp(rip,".pbp")==0)
    {rip[0]='\0'; return NameLength-(strlen(rip)-(strlen(SurFileName)-NameLength));}
    }
    
    //******None Qualified******\//
    
    }//if needed ;)

    //******No Change Needed******\//
    return NameLength;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
char SMenu[350];
void StartList()
{
//Directory is changed in the leftclick area then just read over here!! :)
if ((StartDirectory = opendir(Directory)) == NULL)
{
DisableGraphics();
dprint("error occured while opening the StartDirectory->directory may me invalid");
}
start.current_page=0;
NextPage:
for(start.counter=0; start.counter<=16; start.counter++)
{start.item[start.counter][0]='\0';start.type[start.counter]=-1;}start.type[0]=-1;
if(start.current_page<1){start.counter=15;}
else
{
sprintf(start.item[15],"%s",start.itemhold);
start.type[15]=start.typehold;
start.counter=14;
start.typehold=-1;
start.itemhold[0]='\0';
}

while(start.counter>=0)
{
if((drt = readdir(StartDirectory)) == NULL)break;

if(strcmp(drt->d_name,".")==0||strcmp(drt->d_name,"..")==0||strcmp(drt->d_name,"")==0){continue;/*this prevents built in directory shortcuts&&blanks, yes... I saw a blank before.*/}
sprintf(start.item[start.counter],"%s",drt->d_name);
if((drt->d_stat.st_attr & FIO_SO_IFREG)==1 || (drt->d_stat.st_attr & FIO_SO_IFDIR)==0)//seems to catch all but .bin files so I used ifdir cause it catches .bin
{start.type[start.counter]=1;/*it's a file*/} else{start.type[start.counter]=0;/*it's a folder*/}
start.counter--;
}
if(start.item[0][0]!='\0')
{
sprintf(start.itemhold,"%s",start.item[0]);
start.typehold=start.type[0];
start.type[0]=2;
sprintf(start.item[0],"Next->");
start.more_pages_exists=1;
}
else
{
start.type[0]=-1;
start.item[0][0]='\0';
start.itemhold[0]='\0';
start.typehold=-1;
start.more_pages_exists=0;
}

if(start.current_page<start.page_should_be && start.more_pages_exists==1)
{start.current_page++;goto NextPage;}
start.page_should_be=0;
//loop finished
if (closedir(StartDirectory) == -1)
{
DisableGraphics();
dprint("error occured while closing the StartDirectory");
}
start.counter=0;
while(start.counter<=15)//16 is the back`s display text so it is not altered.
{
sprintf(start.dis_item[start.counter],"%s",start.item[start.counter]);
//start.dis_item[start.counter][(thm.startboard_width-thm.startitems_width)/8]='\0';
start.dis_item[start.counter][Clip_Extension((thm.startboard_width-thm.startitem_width)/8,start.dis_item[start.counter])]='\0';
start.counter++;
}sprintf(start.dis_item[16],"Back*");//above switches dis item to true item not title so it's done here
}//close function

//go back like this so it stays the real string can't use ".." cause it's not programmer friendly :)

int GoBack(char *reversable_dir)
{//begin GoBack();
//char cgg[200];
//sprintf(cgg,"%s",reversable_dir);
if(strlen(reversable_dir)-2>5)//I had to make it six because else it didn't work I think it's because ms0:/\0 was in it/// :'( sorry!!
{
                       int dir_div=strlen(reversable_dir)-2;//only to be used for this function!! :'( sorry...-2 to pass"/\0"
while(reversable_dir[dir_div]!='/')
{
dir_div--;
}
//reversable_dir[(dir_div)+1]='\0';
// +1 so you don't destroy the last "/" :\ I think!
return((dir_div+1));
}return(strlen(reversable_dir));
}//end GoBack();
///////////////////////////////////////////////////////
DIR             *FolderDirectory;
struct dirent   *fldrt;
///////////////////////////////////////////////////////
void Browse(char*fld_to_be_read)
{
     sprintf(fld.dir[fld.active],"%s",fld_to_be_read);
     sprintf(fld2.dis_dir[fld.active],"%s",fld.dir[fld.active]);
     fld2.dis_dir[fld.active][((fld.fullscreen[fld.active]==0?thm.twindow_width:thm.fullscreen_width)/8)-((thm.menu_width*2)/8)]='\0';
     int roundbrw0=(thm.twindow_width/ico.x);
     int roundbrw1=((thm.twindow_height-(thm.menu_height*2))/ico.y);
     if(fld.fullscreen[fld.active]==1)fld.max[fld.active]=32;else fld.max[fld.active]=(roundbrw0*roundbrw1);
     //fld.max[fld.active]=33;
if((FolderDirectory=opendir(fld_to_be_read))!=NULL)
{//<directory openend successfully ;)>
fld.current_page[fld.active]=0;
FldNextPage:
for(fld.counter=0; fld.counter<=fld.max[fld.active]; fld.counter++)
{fld.file[(fld.active*33)+fld.counter][0]='\0';
fld.type[(fld.active*33)+fld.counter]=-1;fld.format[(fld.active*33)+fld.counter]=0;}
if(fld.current_page[fld.active]<1)
{fld.counter=0;}
else
{sprintf(fld.file[(fld.active*33)],"%s",fld.filehold[fld.active]);
fld.type[(fld.active*33)]=fld.typehold[fld.active];fld.counter=1;}
//if(fld.start==1){int fldpage=0; while(fldpage<=16*start.current_page){readdir(FolderDirectory);fldpage++;}fld.start=0;fldpage=0;}//can't apply page value because switching from small to large window will then have errors ;)//fld.current_page[fld.active]=start.current_page;
while(fld.counter<=fld.max[fld.active])
{
                                       if((fldrt = readdir(FolderDirectory)) == NULL)break;
if(strcmp(fldrt->d_name,".")==0 || strcmp(fldrt->d_name,"..")==0||strcmp(fldrt->d_name,"")==0){continue;}
sprintf(fld.file[(fld.active*33)+fld.counter],"%s",fldrt->d_name);
if((fldrt->d_stat.st_attr & FIO_SO_IFREG)==1 || (fldrt->d_stat.st_attr & FIO_SO_IFDIR)==0)
{fld.type[(fld.active*33)+fld.counter]=1;} else{fld.type[(fld.active*33)+fld.counter]=0;}
fld.counter++;
}
if(fld.file[(fld.active*33)+fld.max[fld.active]][0]!='\0')
{
                                         sprintf(fld.filehold[fld.active],"%s",fld.file[(fld.active*33)+fld.max[fld.active]]);
                                         fld.typehold[fld.active]=fld.type[(fld.active*33)+fld.max[fld.active]];
                                         fld.more_pages_exists[fld.active]=1;
}
else
{
     fld.filehold[fld.active][0]='\0';
     fld.typehold[fld.active]=-1;
     fld.more_pages_exists[fld.active]=0;
}

if(fld.current_page[fld.active]<fld.page_should_be[fld.active] && fld.more_pages_exists[fld.active]==1)
{fld.current_page[fld.active]++;goto FldNextPage;}
fld.page_should_be[fld.active]=0;
if (closedir(FolderDirectory) == -1)
{DisableGraphics();dprint("error occured while closing the FolderDirectory");}
fld.counter=0;
while(fld.counter<fld.max[fld.active])//16 is the back`s display text so it is not altered.
{
fld.extension=strrchr(fld.file[(fld.active*33)+fld.counter],'.');
if(fld.type[(fld.active*33)+fld.counter]==0)
{fld.format[(fld.active*33)+fld.counter]=1;}
else
if(fld.extension!=NULL)
{//pass
if(fld.type[(fld.active*33)+fld.counter]==1)
{//ext
//AUDIO
if(stricmp(fld.extension,".mp3")==0||stricmp(fld.extension,".wav")==0
||stricmp(fld.extension,".ogg")==0||stricmp(fld.extension,".mid")==0)
fld.format[(fld.active*33)+fld.counter]=2;
else
//TEXT
if(stricmp(fld.extension,".txt")==0||stricmp(fld.extension,".doc")==0||stricmp(fld.extension,".html")==0||
stricmp(fld.extension,".wri")==0||stricmp(fld.extension,".rtf")==0||stricmp(fld.extension,".log")==0||
stricmp(fld.extension,".vbs")==0||stricmp(fld.extension,".c")==0||stricmp(fld.extension,".c++")==0||
stricmp(fld.extension,".ini")==0)
fld.format[(fld.active*33)+fld.counter]=4;
else
//SCRIPTS
if(stricmp(fld.extension,".script")==0||stricmp(fld.extension,".lua")==0||stricmp(fld.extension,".elf")==0||
stricmp(fld.extension,".prx")==0||stricmp(fld.extension,".pbp")==0)fld.format[(fld.active*33)+fld.counter]=5;
else
//IMAGES
if(stricmp(fld.extension,".jpg")==0||stricmp(fld.extension,".jpeg")==0||stricmp(fld.extension,".png")==0||
stricmp(fld.extension,".gif")==0||stricmp(fld.extension,".tiff")==0||
stricmp(fld.extension,".jpe")==0||stricmp(fld.extension,".ico")==0||
stricmp(fld.extension,".bmp")==0||stricmp(fld.extension,".pbm")==0||
stricmp(fld.extension,".pdd")==0||stricmp(fld.extension,".tga")==0||
stricmp(fld.extension,".pcd")==0||stricmp(fld.extension,".pic")==0||
stricmp(fld.extension,".jfif")==0||stricmp(fld.extension,".pcx")==0||
stricmp(fld.extension,".fax")==0||stricmp(fld.extension,".icb")==0||
stricmp(fld.extension,".win")==0||stricmp(fld.extension,".scr")==0||
stricmp(fld.extension,".vda")==0||stricmp(fld.extension,".emf")==0||
stricmp(fld.extension,".psp")==0)fld.format[(fld.active*33)+fld.counter]=3;
}//ext
}//pass
//else{fld.format[(fld.active*33)+fld.counter]=0;}
sprintf(fld2.dis_file[(fld.active*33)+fld.counter],"%s",fld.file[(fld.active*33)+fld.counter]);
//fld2.dis_file[(fld.active*33)+fld.counter][ico.x/8]='\0';
fld2.dis_file[(fld.active*33)+fld.counter][Clip_Extension(ico.x/8,fld2.dis_file[(fld.active*33)+fld.counter])]='\0';
fld.counter++;
}
}//</directory openend successfully ;)>
}
///////////////////////////////////////////////////////
DIR             *SystemDirectory;
struct dirent   *sysdrt;
//////////////////

void SystemDirRead()
{
if ((SystemDirectory = opendir(sd.dir)) == NULL)
{
DisableGraphics();
dprint("error occured while opening the SystemDirectory->directory may me invalid");
}
else
{
    //no errors opening
sd.current_page=0;
SysNextPage:
for(sd.counter=0; sd.counter<=32; sd.counter++){sd.file[sd.counter][0]='\0';sd.type[sd.counter]=-1;}
if(sd.current_page<1){sd.counter=0;}
else {sd.counter=1;sprintf(sd.file[0],"%s",sd.filehold);sd.type[0]=sd.typehold;sd.typehold=-1;sd.filehold[0]='\0';}

while (sd.counter<=32)
{
      if((sysdrt = readdir(SystemDirectory)) == NULL)break;
if(strcmp(sysdrt->d_name,".")==0||strcmp(sysdrt->d_name,"..")==0||strcmp(sysdrt->d_name,"")==0){continue;}
                                 
                                 char*sysdirext;sysdirext=strrchr(sysdrt->d_name,'.');
//if((sd.category !=1 && sysdrt->d_stat.st_attr & FIO_SO_IFDIR)==0){continue;}
//if(sd.category ==2 && stricmp(sysdirext,".png")!=0){continue;}
sprintf(sd.file[sd.counter],"%s",sysdrt->d_name);
if((sysdrt->d_stat.st_attr & FIO_SO_IFREG)==1 || (sysdrt->d_stat.st_attr & FIO_SO_IFDIR)==0)//seems to catch all but .bin files so I used ifdir cause it catches .bin
{sd.type[sd.counter]=1;} else{sd.type[sd.counter]=0;}
sd.counter++;
}
if(sd.file[32][0]!='\0')
{
sprintf(sd.filehold,"%s",sd.file[32]);
sd.typehold=sd.type[32];
sd.more_pages_exists=1;
}
else
{
sd.filehold[0]='\0';
sd.typehold=-1;
sd.more_pages_exists=0;
}
if(sd.current_page<sd.page_should_be && sd.more_pages_exists==1)
{sd.current_page++;goto SysNextPage;}
sd.page_should_be=0;
//loop finished
if (closedir(SystemDirectory) == -1)
{
DisableGraphics();
dprint("error occured while closing the SystemDirectory");
}
sd.counter=0;
while(sd.counter<=31)
{
sprintf(sd.dis_file[sd.counter],"%s",sd.file[sd.counter]);
//sd.dis_file[sd.counter][ico.x/8]='\0';
sd.dis_file[sd.counter][Clip_Extension(ico.x/8,sd.dis_file[sd.counter])]='\0';
sd.counter++;
}
}//no errors opening
}//close function <-
//*****************************************************
int ReadTextSheets()
{
     FILE* notebook;
if((notebook=fopen(txt.file[txt.active],"r"))!=NULL)
{
txt.size_in_bytes[txt.active]=sizeof(notebook);
rewind(notebook);
//40 letters across are accepted because 320/8 320=txtback width 8=char width(small)
//60 letters across are accepted because thm.fullscreen_height/8 320=txtback width 8=char width(large)
for(txt.count=0; txt.count<(thm.fullscreen_height/(8*2))-1; txt.count++)txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count][0]='\0';

for(txt.count=0; txt.count<txt.scroll[txt.active]; txt.count++)if((fgets(txt.lines[txt.active*(thm.fullscreen_height/(8*2))],( (txt.fullscreen[txt.active]==1?thm.fullscreen_width:thm.twindow_width) /8)+1, notebook))==NULL){if(txt.scroll[txt.active]>0)txt.scroll[txt.active]--; fclose(notebook);return(-1);}//skip passed lines large passes to zero cause zero is not shown

if(txt.fullscreen[txt.active]==1)
{
for(txt.count=1; txt.count<=(272-(thm.menu_height+(8*2)))/(8*2); txt.count++)
{//loop
fgets(txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count],(thm.fullscreen_width/8)+1, notebook);
if(txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count][strlen(txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count])-1]=='\n')
{  txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count][strlen(txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count])-1]='\0';}//attempt removal of newline
if(txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count][strlen(txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count])-1]=='\r')
{  txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count][strlen(txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count])-1]='\0';}//attempt removal of return
if(txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count][strlen(txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count])-1]=='\f')
{  txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count][strlen(txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count])-1]='\0';}//attempt removal of form feed
}//loop
}
else
{
for(txt.count=1; txt.count<=(thm.twindow_height-(thm.menu_height+(8*2)))/(8*2); txt.count++)
{//loop2
fgets(txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count],(thm.twindow_width/8)+1, notebook);
if(txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count][strlen(txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count])-1]=='\n')
{  txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count][strlen(txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count])-1]='\0';}//attempt removal of newline
if(txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count][strlen(txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count])-1]=='\r')
{  txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count][strlen(txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count])-1]='\0';}//attempt removal of return
if(txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count][strlen(txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count])-1]=='\f')
{  txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count][strlen(txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.count])-1]='\0';}//attempt removal of form feed
}//loop2
}
fclose(notebook);
}//end if no errors from open occurs!
else{dprint("Please report this error and the materials involved along with your last 5 activities and the file selected.");return(-2);}
return(0);
}//end function
//*****************************************************Imaging script retrieved from psp-programming Forums: http://www.psp-programming.com/dev-forum/viewtopic.php?t=438&start=30&sid=7b79f01b0c1a31b9880e782ba7d9345d
   // @param x_pos, y_pos, width, height : where to draw the image to and how big it is on screen 
   // @param u0, v0, u1, v1 : the image part which is to be drawn, (0,0,imagewidth,imageheight) for the whole image 
struct VertexNoColor 
{ 
float u, v; 
short x, y, z; 
};
void RenderImage(char* Image,int u0,int v0,int u1,int v1,int x_pos,int y_pos,int width,int height)
{
   float start, end; 
   float cur_u = u0; 
   float cur_x = x_pos; 
   float x_end = x_pos + width; 
   float slice = 64.f; 
   float ustep = (float)(u1-u0)/(float)width * slice;
//*******
   // blit maximizing the use of the texture-cache 
   for( start=0, end=width; start<end; start+=slice ) 
      { 
      struct VertexNoColor* vertices = (struct VertexNoColor*)sceGuGetMemory(2 * sizeof(struct VertexNoColor)); 

      float poly_width = ((cur_x+slice) > x_end) ? (x_end-cur_x) : slice; 
      float source_width = ((cur_u+ustep) > u1) ? (u1-cur_u) : ustep; 
//*******
      vertices[0].u = cur_u; 
      vertices[0].v = v0; 
      vertices[0].x = cur_x; 
      vertices[0].y = y_pos; 
      vertices[0].z = 0; 
//*******
      cur_u += source_width; 
      cur_x += poly_width; 
//*******
      vertices[1].u = cur_u; 
      vertices[1].v = v1; 
      vertices[1].x = cur_x; 
      vertices[1].y = (y_pos + height); 
      vertices[1].z = 0; 

      sceGuDrawArray(GU_SPRITES,GU_TEXTURE_32BITF|GU_VERTEX_16BIT|GU_TRANSFORM_2D,2,0,vertices); 
      }
}//end function
//*****************************************************Imaging script retrieved from psp-programming Forums: http://www.psp-programming.com/dev-forum/viewtopic.php?t=438&start=30&sid=7b79f01b0c1a31b9880e782ba7d9345d
//////////////////
clearDebug();
pspDebugScreenSetTextColor(rgb(248,248,0));
dprint("Loading Cursor Structure and Variables...");halt(9);
////Cursor
struct Mouse
{
       int x;
       int y;
       int lag;
       float speed;
}cursor;
cursor.x=240;
cursor.y=136;
cursor.lag=0;
cursor.speed=2;
//////////////////



//////////////////
clearDebug();
pspDebugScreenSetTextColor(rgb(0,0,255));
dprint("Initiating Various System Modes and Variables...");halt(9);
/////////////Call Various System Variables
SceUID openfile;
////////PULL MOUSE NOW///////\*
clearDebug();
pspDebugScreenSetTextColor(rgb(250,250,250));
dprint("Preparing Controllers...");halt(9);
///////////////
sceCtrlSetSamplingCycle(0);
sceCtrlSetSamplingMode(0);
int LastButton;
/////////////////////////\*
clearDebug();
pspDebugScreenSetTextColor(rgb(250,0,250));
dprint("Loading External Data...");halt(9);
///////////////
char usertheme[350];
char swallpaper[350];
char username[350];
int FileSize;
//sprintf(usertheme,"Test");
//WALLPAPER
openfile = sceIoOpen("ms0:/XT1-OS/System/Structure/Wallpaper", PSP_O_RDONLY|PSP_O_CREAT,0);
FileSize = sceIoLseek (openfile, 0, SEEK_END);
sceIoLseek(openfile,0,SEEK_SET);
sceIoRead(openfile,swallpaper,FileSize);
sceIoClose (openfile);
//FIX*********************\//
swallpaper[FileSize]=0x00;///
//************************\//
//USERTHEME
void Read_User_Theme()
{
openfile = sceIoOpen("ms0:/XT1-OS/System/Structure/Theme",PSP_O_RDONLY|PSP_O_CREAT,0);
FileSize = sceIoLseek (openfile, 0, SEEK_END);
sceIoLseek(openfile,0,SEEK_SET);
sceIoRead(openfile,usertheme,FileSize);
sceIoClose (openfile);
//FIX********************\//
usertheme[FileSize]=0x00;///
//***********************\//
}Read_User_Theme();
//\*******************HEX COLORS
clr.count=0;
while(clr.count<=7)
{
sprintf(clr.dir,"ms0:/XT1-OS/System/Resources/Themes/%s/Config/%s",usertheme,clr.system[clr.count]);
openfile = sceIoOpen(clr.dir,PSP_O_RDONLY|PSP_O_CREAT,0);
FileSize = sceIoLseek (openfile, 0, SEEK_END);
sceIoLseek(openfile,0,SEEK_SET);
sceIoRead(openfile,clr.conversion_unit,9);
sceIoClose (openfile);
//Debug Test Display
clr.conversion_unit[9]=0x00;
//clr.conversion_unit[9]='\0';
clearDebug();
dprint(clr.system[clr.count]);dprint("\n");
dprint(clr.conversion_unit);halt(125);
//Debug Test Display
//--//--//--//------------break------------//--//--//--//
//COLOR MENDING PROCESS<-
memcpy(clr.red[clr.count],clr.conversion_unit,3);clr.red[clr.count][3]='\0';//red
memcpy(clr.grn[clr.count],clr.conversion_unit+3,3);clr.grn[clr.count][3]='\0';//green
memcpy(clr.blu[clr.count],clr.conversion_unit+6,3);clr.blu[clr.count][3]='\0';//blue
//COLOR MENDING PROCESS<-
clr.count++;
}
//**************************System - Graphics**********************************/
clearDebug();
pspDebugScreenSetTextColor(rgb(0,250,250));
dprint("Preparing Graphics...");halt(9);
char graphics[380];
    Image *startbar;
    Image *topmenu;
    Image *mainscreen;
    Image *scursor;
    Image *folder0;
    Image *folder1;
    Image *button0;
    Image *button1;
    Image *scrntime;
    Image *scrnbtry;
    Image *select;
    Image *strt0;
    Image *strt1;
    Image *strt2;
    Image *strtl;
    Image *browse0;
    Image *browse1;
    Image *setting0;
    Image *setting1;
    Image *themes0;
    Image *themes1;
    Image *startexit0;
    Image *startexit1;
    ////////////////////THEMES
    Image *sttnwallpaper0;
    Image *sttnwallpaper1;
    Image *sttnsettings0;
    Image *sttnsettings1;
    ////////////////////THEMES
    //Files
    Image *Fpic0;
    Image *Fpic1;
    Image *Faud0;
    Image *Faud1;
    Image *Ftxt0;
    Image *Ftxt1;
    Image *Funk0;//unknown<-
    Image *Funk1;//unknown<-
    Image *Fpbp0;
    Image *Fpbp1;
    //battery
    Image *b0;//highest
    Image *b1;
    Image *b2;
    Image *b3;
    Image *b4;
    Image *b5;
    Image *b6;
    Image *b7;
    Image *b8;
    Image *b9;
    Image *bchrg;
    //battery end
    Image *bgpic;
    //programs frames
    Image *audtop;
    Image *audwindow;
    Image *vidtop;
    //vid has no large, it should push to fullscreen :)
    //programs accessories
    //buttons
    //audio addons
    Image *audplay0;
    Image *audpause0;
    Image *audstop0;
    Image *audskpf0;
    Image *audskpb0;
    Image *audsizeswt0;
    Image *audexit0;
    Image *audloop0;
    Image *audshuff0;
    Image *audcycle0;
    //below are mouse overs :)
    Image *audplay1;
    Image *audpause1;
    Image *audstop1;
    Image *audskpf1;
    Image *audskpb1;
    Image *audsizeswt1;
    Image *audexit1;
    Image *audloop1;
    Image *audshuff1;
    Image *audcycle1;
    //below are the pics which have a 3rd theme :)
    //if loop is on etc...
    Image *audloop2;
    Image *audshuff2;
    Image *audcycle2;
    //video addons
    Image *vidplay0;
    Image *vidpause0;
    Image *vidstop0;
    Image *vidskpf0;
    Image *vidskpb0;
    Image *vidsizeswt0;
    Image *vidloop0;
    Image *videxit0;
    //below are the pics which have a 3rd theme :)
    Image *vidplay1;
    Image *vidpause1;
    Image *vidstop1;
    Image *vidskpf1;
    Image *vidskpb1;
    Image *vidsizeswt1;
    Image *vidloop1;
    Image *videxit1;
    //3rd theme pics for video :)
    Image *vidloop2;
    //text addons
    Image *txtexit0;
    Image *txtsizeswt0;
    Image *txtbck0;
    Image *txtfwd0;
    //txt mouse overs
    Image *txtexit1;
    Image *txtsizeswt1;
    Image *txtbck1;
    Image *txtfwd1;
    //program backs
    //txt
    Image *txtback0;//background behind text when compact :)
    Image *txtback1;//background behind text when fullscreen :)
    //video
    Image *vidback0;//compact layed behind video
    Image *vidback1;//480xthm.fullscreen_height layed behind video
    //program screens
    //video
    Image *vcmpctscrn0;//layed over video... should be see through for best result kindof for changing video coloring
    Image *vcmpctscrn1;
    Image *vlargescrn0;
    Image *vlargescrn1;
    //////////////////
    //FOLDER PROGRAM//////
    Image *fldback0;//non-fullscreen<--
    Image *fldback1;//fullscreen<--
    Image *fldsizeswt0;//|_|
    Image *fldsizeswt1;//|_|
    Image *fldfwd0;//arrow
    Image *fldfwd1;//arrow
    Image *fldbck0;//arrow
    Image *fldbck1;//arrow
    Image *fldexit0;//////
    Image *fldexit1;//////
    //////////////////////
    //SYSTEM SETTINGS/////
    Image *sttselection;//
    Image *sttexit0;//////
    Image *sttexit1;//////
    //////////////////////
    //MESSAGE WINDOWS/////
    Image *msgexit0;//////
    Image *msgexit1;//////
    Image *msgbody;///////
    Image *msgbutton0;////
    Image *msgbutton1;////
    //////////////////////
//SYSTEM RESOURCES ONLY!!
Image *systemform0;//////
/////////////////////////
void Unload_Theme()
{
//REMOVE ALL LOADED ART!!
    /*freeImage(startbar);
    freeImage(topmenu);
    freeImage(mainscreen);
    freeImage(scursor);
    freeImage(folder0);
    freeImage(folder1);
    freeImage(button0);
    freeImage(button1);
    freeImage(scrntime);
    freeImage(scrnbtry);
    freeImage(select);
    freeImage(strt0);
    freeImage(strt1);
    freeImage(strt2);
    freeImage(strtl);
    freeImage(browse0);
    freeImage(browse1);
    freeImage(setting0);
    freeImage(setting1);
    freeImage(themes0);
    freeImage(themes1);
    freeImage(startexit0);
    freeImage(startexit1);
    ////////////////////THEMES
    freeImage(sttnwallpaper0);
    freeImage(sttnwallpaper1);
    freeImage(sttnsettings0);
    freeImage(sttnsettings1);
    ////////////////////THEMES
    //Files
    freeImage(Fpic0);
    freeImage(Fpic1);
    freeImage(Faud0);
    freeImage(Faud1);
    freeImage(Ftxt0);
    freeImage(Ftxt1);
    freeImage(Funk0);//unknown<-
    freeImage(Funk1);//unknown<-
    freeImage(Fpbp0);
    freeImage(Fpbp1);
    //battery
    freeImage(b0);//highest
    freeImage(b1);
    freeImage(b2);
    freeImage(b3);
    freeImage(b4);
    freeImage(b5);
    freeImage(b6);
    freeImage(b7);
    freeImage(b8);
    freeImage(b9);
    freeImage(bchrg);
    //battery end
    freeImage(bgpic);
    //programs frames
    freeImage(audtop);
    freeImage(audwindow);
    freeImage(vidtop);
    //vid has no large, it should push to fullscreen :)
    //programs accessories
    //buttons
    //audio addons
    freeImage(audplay0);
    freeImage(audpause0);
    freeImage(audstop0);
    freeImage(audskpf0);
    freeImage(audskpb0);
    freeImage(audsizeswt0);
    freeImage(audexit0);
    freeImage(audloop0);
    freeImage(audshuff0);
    freeImage(audcycle0);
    //below are mouse overs :)
    freeImage(audplay1);
    freeImage(audpause1);
    freeImage(audstop1);
    freeImage(audskpf1);
    freeImage(audskpb1);
    freeImage(audsizeswt1);
    freeImage(audexit1);
    freeImage(audloop1);
    freeImage(audshuff1);
    freeImage(audcycle1);
    //below are the pics which have a 3rd theme :)
    //if loop is on etc...
    freeImage(audloop2);
    freeImage(audshuff2);
    freeImage(audcycle2);
    //video addons
    freeImage(vidplay0);
    freeImage(vidpause0);
    freeImage(vidstop0);
    freeImage(vidskpf0);
    freeImage(vidskpb0);
    freeImage(vidsizeswt0);
    freeImage(vidloop0);
    freeImage(videxit0);
    //below are the pics which have a 3rd theme :)
    freeImage(vidplay1);
    freeImage(vidpause1);
    freeImage(vidstop1);
    freeImage(vidskpf1);
    freeImage(vidskpb1);
    freeImage(vidsizeswt1);
    freeImage(vidloop1);
    freeImage(videxit1);
    //3rd theme pics for video :)
    freeImage(vidloop2);
    //text addons
    freeImage(txtexit0);
    freeImage(txtsizeswt0);
    freeImage(txtbck0);
    freeImage(txtfwd0);
    //txt mouse overs
    freeImage(txtexit1);
    freeImage(txtsizeswt1);
    freeImage(txtbck1);
    freeImage(txtfwd1);
    //program backs
    //txt
    freeImage(txtback0);//background behind text when compact :)
    freeImage(txtback1);//background behind text when fullscreen :)
    //video
    freeImage(vidback0);//compact layed behind video
    freeImage(vidback1);//480xthm.fullscreen_height layed behind video
    //program screens
    //video
    freeImage(vcmpctscrn0);//layed over video... should be see through for best result kindof for changing video coloring
    freeImage(vcmpctscrn1);
    freeImage(vlargescrn0);
    freeImage(vlargescrn1);
    //////////////////
    //FOLDER PROGRAM//////
    freeImage(fldback0);//non-fullscreen<--
    freeImage(fldback1);//fullscreen<--
    freeImage(fldfwd0);//arrow
    freeImage(fldfwd1);//arrow
    freeImage(fldbck0);//arrow
    freeImage(fldbck1);//arrow
    freeImage(fldexit0);//////
    freeImage(fldexit1);//////
    //////////////////////
    //SYSTEM SETTINGS/////
    freeImage(sttselection);//
    freeImage(sttexit0);//////
    freeImage(sttexit1);//////
    //////////////////////
    //MESSAGE WINDOWS/////
    freeImage(msgexit0);//////
    freeImage(msgexit1);//////
    freeImage(msgbody);///////
    freeImage(msgbutton0);////
    freeImage(msgbutton1);////
    
*/}

//LOAD MAIN PORTIONS OF OPERATING SYSTEM.
clearDebug();
pspDebugScreenSetTextColor(rgb(255,128,0));
dprint("Inserting Graphics...");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/MainFrames/Bottom.png",usertheme);clearDebug();
    startbar=insertpx(graphics);dprint("\n1");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/MainFrames/Top.png",usertheme);clearDebug();
    topmenu=insertpx(graphics);dprint("\n2");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Screens/Scr0.png",usertheme);clearDebug();
    mainscreen=insertpx(graphics);dprint("\n3");halt(9);
    //SYSTEM DIRECTORY BELOW -->
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Wallpaper/%s",swallpaper);clearDebug();
    bgpic=insertpx(graphics);dprint("\n4");halt(9);
    //LOAD SYSTEM PORTION OF OPERATING SYSTEM.
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/SystsemIcons/Cursor.png",usertheme);clearDebug();
    scursor=insertpx(graphics);dprint("\n5");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/SystsemIcons/B0.png",usertheme);clearDebug();
    button0=insertpx(graphics);dprint("\n6");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/SystsemIcons/B1.png",usertheme);clearDebug();
    button1=insertpx(graphics);dprint("\n7");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/SystsemIcons/F0.png",usertheme);clearDebug();
    folder0=insertpx(graphics);dprint("\n-");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/SystsemIcons/F1.png",usertheme);clearDebug();
    folder1=insertpx(graphics);dprint("\n--");halt(9);
    //LOAD SCREEN PORTION OF OPERATING SYSTEM.
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Screens/ScrT.png",usertheme);clearDebug();
    scrntime=insertpx(graphics);dprint("\nscrntime.");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Screens/ScrB.png",usertheme);clearDebug();
    scrnbtry=insertpx(graphics);dprint("\nscrnbtry.");halt(9);
    //LOAD START PORTION OF OPERATING SYSTEM.
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/S0.png",usertheme);clearDebug();
    strt0=insertpx(graphics);dprint("\n8");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/S1.png",usertheme);clearDebug();
    strt1=insertpx(graphics);dprint("\n9");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/S2.png",usertheme);clearDebug();
    strt2=insertpx(graphics);dprint("\n10");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/Sl.png",usertheme);clearDebug();
    strtl=insertpx(graphics);dprint("\n-");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/Sc.png",usertheme);clearDebug();
    select=insertpx(graphics);dprint("\n--");halt(9);
//start buttons
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/Brws0.PNG",usertheme);clearDebug();
    browse0=insertpx(graphics);dprint("\n---");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/Brws1.PNG",usertheme);clearDebug();
    browse1=insertpx(graphics);dprint("\n----");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/Sttn0.PNG",usertheme);clearDebug();
    setting0=insertpx(graphics);dprint("\n-----");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/Sttn1.PNG",usertheme);clearDebug();
    setting1=insertpx(graphics);dprint("\n------");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/Thms0.PNG",usertheme);clearDebug();
    themes0=insertpx(graphics);dprint("\n-------");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/Thms1.PNG",usertheme);clearDebug();
    themes1=insertpx(graphics);dprint("\n--------");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/Ex0.PNG",usertheme);clearDebug();
    startexit0=insertpx(graphics);dprint("\n---------");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/Ex1.PNG",usertheme);clearDebug();
    startexit1=insertpx(graphics);dprint("\n11");halt(9);
    //LOAD BATTERY PORTION OF OPERATING SYSTEM.
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/0.png",usertheme);clearDebug();//HIGH//
    b0=insertpx(graphics);dprint("\n12");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/1.png",usertheme);clearDebug();//HIGH//
    b1=insertpx(graphics);dprint("\n13");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/2.png",usertheme);clearDebug();//HIGH//
    b2=insertpx(graphics);dprint("\n14");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/3.png",usertheme);clearDebug();//HIGH//
    b3=insertpx(graphics);dprint("\n15");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/4.png",usertheme);clearDebug();//MEDM//
    b4=insertpx(graphics);dprint("\n16");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/5.png",usertheme);clearDebug();//MEDM//
    b5=insertpx(graphics);dprint("\n17");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/6.png",usertheme);clearDebug();//DEAD//
    b6=insertpx(graphics);dprint("\n18");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/7.png",usertheme);clearDebug();//DEAD//
    b7=insertpx(graphics);dprint("\n19");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/8.png",usertheme);clearDebug();//DEAD//
    b8=insertpx(graphics);dprint("\n20");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/9.png",usertheme);clearDebug();//DEAD//
    b9=insertpx(graphics);dprint("\n21");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/10.png",usertheme);clearDebug();//CURRENTLY CHARGING//
    bchrg=insertpx(graphics);dprint("\n22");halt(9);
    //Files
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Files/Aud0.png",usertheme);clearDebug();
    Faud0=insertpx(graphics);dprint("\nF1");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Files/Aud1.png",usertheme);clearDebug();
    Faud1=insertpx(graphics);dprint("\nF2");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Files/Pic0.png",usertheme);clearDebug();
    Fpic0=insertpx(graphics);dprint("\nF3");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Files/Pic1.png",usertheme);clearDebug();
    Fpic1=insertpx(graphics);dprint("\nF4");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Files/Txt0.png",usertheme);clearDebug();
    Ftxt0=insertpx(graphics);dprint("\nF5");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Files/Txt1.png",usertheme);clearDebug();
    Ftxt1=insertpx(graphics);dprint("\nF6");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Files/Pbp0.png",usertheme);clearDebug();
    Fpbp0=insertpx(graphics);dprint("\nF7");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Files/Pbp1.png",usertheme);clearDebug();
    Fpbp1=insertpx(graphics);dprint("\nF8");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Files/UNKNOWN0.png",usertheme);clearDebug();
    Funk0=insertpx(graphics);dprint("\nF9");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Files/UNKNOWN1.png",usertheme);clearDebug();
    Funk1=insertpx(graphics);dprint("\nF10");halt(9);
    ///////
    //LOAD PROGRAMS PORTION OF OPERATING SYSTEM.
    clearDebug();dprint("Inserting Program Graphics...");halt(9);
    //LABELED SYSTEM PICS
    //ADDONS->
    //to prevent overlooking of materials, program pics will mainly be done in order of declaration not priority :)
    //frames
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/Bar.png",usertheme);
    audtop=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/Wnd.png",usertheme);
    audwindow=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/Bar.png",usertheme);
    vidtop=insertpx(graphics);
    ////accessories
    //AUDIO
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/P0.PNG",usertheme);
    audplay0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/Q0.PNG",usertheme);
    audpause0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/S0.PNG",usertheme);
    audstop0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/F0.PNG",usertheme);
    audskpf0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/R0.PNG",usertheme);
    audskpb0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/Z0.PNG",usertheme);
    audsizeswt0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/X0.PNG",usertheme);
    audexit0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/L0.PNG",usertheme);
    audloop0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/H0.PNG",usertheme);
    audshuff0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/N0.PNG",usertheme);
    audcycle0=insertpx(graphics);
    //
    //VIDEO
    ////accessories
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/P0.PNG",usertheme);
    vidplay0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/Q0.PNG",usertheme);
    vidpause0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/S0.PNG",usertheme);
    vidstop0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/F0.PNG",usertheme);
    vidskpf0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/R0.PNG",usertheme);
    vidskpb0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/Z0.PNG",usertheme);
    vidsizeswt0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/X0.PNG",usertheme);
    videxit0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/L0.PNG",usertheme);
    vidloop0=insertpx(graphics);
    //
    //TEXT - NOTEPAD
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Text/X0.PNG",usertheme);
    txtexit0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Text/Z0.PNG",usertheme);
    txtsizeswt0=insertpx(graphics);
    //
    ////////////////////////MOUSE OVERS
    //AUDIO
    ////accessories
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/P1.PNG",usertheme);
    audplay1=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/Q1.PNG",usertheme);
    audpause1=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/S1.PNG",usertheme);
    audstop1=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/F1.PNG",usertheme);
    audskpf1=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/R1.PNG",usertheme);
    audskpb1=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/Z1.PNG",usertheme);
    audsizeswt1=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/X1.PNG",usertheme);
    audexit1=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/L1.PNG",usertheme);
    audloop1=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/H1.PNG",usertheme);
    audshuff1=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/N1.PNG",usertheme);
    audcycle1=insertpx(graphics);
    //
    //VIDEO
    ////accessories
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/P1.PNG",usertheme);
    vidplay1=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/Q1.PNG",usertheme);
    vidpause1=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/S1.PNG",usertheme);
    vidstop1=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/F1.PNG",usertheme);
    vidskpf1=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/R1.PNG",usertheme);
    vidskpb1=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/Z1.PNG",usertheme);
    vidsizeswt1=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/X1.PNG",usertheme);
    videxit1=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/L1.PNG",usertheme);
    vidloop1=insertpx(graphics);
    //
    //TEXT - NOTEPAD
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Text/X1.PNG",usertheme);
    txtexit1=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Text/Z1.PNG",usertheme);
    txtsizeswt1=insertpx(graphics);
    //
    ////////////////////////3RD PORTIONS
    //AUDIO
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/L2.PNG",usertheme);
    audloop2=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/H2.PNG",usertheme);
    audshuff2=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/N2.PNG",usertheme);
    audcycle2=insertpx(graphics);
    //
    //VIDEO
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/L2.PNG",usertheme);
    vidloop2=insertpx(graphics);
    //
    ////////////////////////BACKS AND SCREENS
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/CBase.PNG",usertheme);
    vidback0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/FBase.PNG",usertheme);
    vidback1=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Text/CScrn.PNG",usertheme);
    txtback0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Text/FScrn.PNG",usertheme);
    txtback1=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Folders/ScrnC.PNG",usertheme);
    fldback0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Folders/ScrnF.PNG",usertheme);
    fldback1=insertpx(graphics);
    //
    ////////////////////////PROGRAM SCREENS
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/CScrn0.PNG",usertheme);
    vcmpctscrn0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/CScrn1.PNG",usertheme);
    vcmpctscrn1=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/FScrn0.PNG",usertheme);
    vlargescrn0=insertpx(graphics);
    //
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/FScrn1.PNG",usertheme);
    vlargescrn1=insertpx(graphics);
    //
    ////////////////////////SETTINGS
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Settings/Selection.PNG",usertheme);
    sttselection=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Settings/X0.PNG",usertheme);
    sttexit0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Settings/X1.PNG",usertheme);
    sttexit1=insertpx(graphics);
    ////////////////////////SETTINGS
    ////////////////////////MSG_WINDOWS
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/MsgFrames/X0.PNG",usertheme);
    msgexit0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/MsgFrames/X1.PNG",usertheme);
    msgexit1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/MsgFrames/Body.PNG",usertheme);
    msgbody=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/MsgFrames/B0.PNG",usertheme);
    msgbutton0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/MsgFrames/B1.PNG",usertheme);
    msgbutton1=insertpx(graphics);
    ////////////////////////MSG_WINDOWS
    //FOLDER PORTIONS///////
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Folders/X0.PNG",usertheme);
    fldexit0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Folders/X1.PNG",usertheme);
    fldexit1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Folders/Z0.PNG",usertheme);
    fldsizeswt0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Folders/Z1.PNG",usertheme);
    fldsizeswt1=insertpx(graphics);
    ////////////////////////PROGRAM ARROWS
    //TEXT
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Text/B0.PNG",usertheme);
    txtbck0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Text/B1.PNG",usertheme);
    txtbck1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Text/B2.PNG",usertheme);
    txtfwd0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Text/B3.PNG",usertheme);
    txtfwd1=insertpx(graphics);
    //FOLDERS
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Folders/B0.PNG",usertheme);
    fldbck0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Folders/B1.PNG",usertheme);
    fldbck1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Folders/B2.PNG",usertheme);
    fldfwd0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Folders/B3.PNG",usertheme);
    fldfwd1=insertpx(graphics);
    ////////////////////////PROGRAM ARROWS
    //////////////////////////////////////////THEMES
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/SystsemIcons/Wall0.png",usertheme);clearDebug();
    sttnwallpaper0=insertpx(graphics);dprint("\n5");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/SystsemIcons/Wall1.png",usertheme);clearDebug();
    sttnwallpaper1=insertpx(graphics);dprint("\n5");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/SystsemIcons/Sttn0.png",usertheme);clearDebug();
    sttnsettings0=insertpx(graphics);dprint("\n5");halt(9);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/SystsemIcons/Sttn1.png",usertheme);clearDebug();
    sttnsettings1=insertpx(graphics);dprint("\n5");halt(9);
    //////////////////////////////////////////THEMES
    ////////////////////////
    //FINISH ADDING LOADS LATER...
//************************************************************WILL ALTER THIS TO BE ORIGINAL LATER, BUT THE OTHER IS NEEDED FOR TESTING CAUSE THE DEBUG COLOR CHANGES WHEN THE PROGRAM IS BROKE ETC...
void Load_Theme()
{/*
//loading of theme is finished <-- STR FUNCTION''
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/MainFrames/Bottom.png",usertheme);
    startbar=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/MainFrames/Top.png",usertheme);
    topmenu=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Screens/Scr0.png",usertheme);
    mainscreen=insertpx(graphics);
    //SYSTEM DIRECTORY BELOW -->
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Wallpaper/%s",swallpaper);
    bgpic=insertpx(graphics);
    //LOAD SYSTEM PORTION OF OPERATING SYSTEM.
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/SystsemIcons/Cursor.png",usertheme);
    scursor=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/SystsemIcons/B0.png",usertheme);
    button0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/SystsemIcons/B1.png",usertheme);
    button1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/SystsemIcons/F0.png",usertheme);
    folder0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/SystsemIcons/F1.png",usertheme);
    folder1=insertpx(graphics);
    //LOAD SCREEN PORTION OF OPERATING SYSTEM.
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Screens/ScrT.png",usertheme);
    scrntime=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Screens/ScrB.png",usertheme);
    scrnbtry=insertpx(graphics);
    //LOAD START PORTION OF OPERATING SYSTEM.
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/S0.png",usertheme);
    strt0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/S1.png",usertheme);
    strt1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/S2.png",usertheme);
    strt2=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/Sl.png",usertheme);
    strtl=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/Sc.png",usertheme);
    select=insertpx(graphics);
//start buttons
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/Brws0.PNG",usertheme);
    browse0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/Brws1.PNG",usertheme);
    browse1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/Sttn0.PNG",usertheme);
    setting0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/Sttn1.PNG",usertheme);
    setting1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/Thms0.PNG",usertheme);
    themes0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/Thms1.PNG",usertheme);
    themes1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/Ex0.PNG",usertheme);
    startexit0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Start/Ex1.PNG",usertheme);
    startexit1=insertpx(graphics);
    //LOAD BATTERY PORTION OF OPERATING SYSTEM.
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/0.png",usertheme);
    b0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/1.png",usertheme);
    b1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/2.png",usertheme);
    b2=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/3.png",usertheme);
    b3=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/4.png",usertheme);
    b4=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/5.png",usertheme);
    b5=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/6.png",usertheme);
    b6=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/7.png",usertheme);
    b7=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/8.png",usertheme);
    b8=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/9.png",usertheme);
    b9=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Battery/10.png",usertheme);
    bchrg=insertpx(graphics);
    //Files
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Files/Aud0.png",usertheme);
    Faud0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Files/Aud1.png",usertheme);
    Faud1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Files/Pic0.png",usertheme);
    Fpic0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Files/Pic1.png",usertheme);
    Fpic1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Files/Txt0.png",usertheme);
    Ftxt0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Files/Txt1.png",usertheme);
    Ftxt1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Files/Pbp0.png",usertheme);
    Fpbp0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Files/Pbp1.png",usertheme);
    Fpbp1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Files/UNKNOWN0.png",usertheme);
    Funk0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Files/UNKNOWN1.png",usertheme);
    Funk1=insertpx(graphics);
    ///////
    //LOAD PROGRAMS PORTION OF OPERATING SYSTEM.
    //LABELED SYSTEM PICS
    //ADDONS->
    //to prevent overlooking of materials, program pics will mainly be done in order of declaration not priority :)
    //frames
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/Bar.png",usertheme);
    audtop=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/Wnd.png",usertheme);
    audwindow=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/Bar.png",usertheme);
    vidtop=insertpx(graphics);
    ////accessories
    //AUDIO
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/P0.PNG",usertheme);
    audplay0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/Q0.PNG",usertheme);
    audpause0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/S0.PNG",usertheme);
    audstop0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/F0.PNG",usertheme);
    audskpf0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/R0.PNG",usertheme);
    audskpb0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/Z0.PNG",usertheme);
    audsizeswt0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/X0.PNG",usertheme);
    audexit0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/L0.PNG",usertheme);
    audloop0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/H0.PNG",usertheme);
    audshuff0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/N0.PNG",usertheme);
    audcycle0=insertpx(graphics);
    //VIDEO
    ////accessories
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/P0.PNG",usertheme);
    vidplay0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/Q0.PNG",usertheme);
    vidpause0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/S0.PNG",usertheme);
    vidstop0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/F0.PNG",usertheme);
    vidskpf0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/R0.PNG",usertheme);
    vidskpb0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/Z0.PNG",usertheme);
    vidsizeswt0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/X0.PNG",usertheme);
    videxit0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/L0.PNG",usertheme);
    vidloop0=insertpx(graphics);
    //TEXT - NOTEPAD
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Text/X0.PNG",usertheme);
    txtexit0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Text/Z0.PNG",usertheme);
    txtsizeswt0=insertpx(graphics);
    ////////////////////////MOUSE OVERS
    //AUDIO
    ////accessories
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/P1.PNG",usertheme);
    audplay1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/Q1.PNG",usertheme);
    audpause1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/S1.PNG",usertheme);
    audstop1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/F1.PNG",usertheme);
    audskpf1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/R1.PNG",usertheme);
    audskpb1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/Z1.PNG",usertheme);
    audsizeswt1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/X1.PNG",usertheme);
    audexit1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/L1.PNG",usertheme);
    audloop1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/H1.PNG",usertheme);
    audshuff1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/N1.PNG",usertheme);
    audcycle1=insertpx(graphics);
    //VIDEO
    ////accessories
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/P1.PNG",usertheme);
    vidplay1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/Q1.PNG",usertheme);
    vidpause1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/S1.PNG",usertheme);
    vidstop1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/F1.PNG",usertheme);
    vidskpf1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/R1.PNG",usertheme);
    vidskpb1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/Z1.PNG",usertheme);
    vidsizeswt1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/X1.PNG",usertheme);
    videxit1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/L1.PNG",usertheme);
    vidloop1=insertpx(graphics);
    //TEXT - NOTEPAD
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Text/X1.PNG",usertheme);
    txtexit1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Text/Z1.PNG",usertheme);
    txtsizeswt1=insertpx(graphics);
    ////////////////////////3RD PORTIONS
    //AUDIO
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/L2.PNG",usertheme);
    audloop2=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/H2.PNG",usertheme);
    audshuff2=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Audio/N2.PNG",usertheme);
    audcycle2=insertpx(graphics);
    //VIDEO
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/L2.PNG",usertheme);
    vidloop2=insertpx(graphics);
    ////////////////////////BACKS AND SCREENS
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/CBase.PNG",usertheme);
    vidback0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/FBase.PNG",usertheme);
    vidback1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Text/CScrn.PNG",usertheme);
    txtback0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Text/FScrn.PNG",usertheme);
    txtback1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Folders/ScrnC.PNG",usertheme);
    fldback0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Folders/ScrnF.PNG",usertheme);
    fldback1=insertpx(graphics);
    ////////////////////////PROGRAM SCREENS
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/CScrn0.PNG",usertheme);
    vcmpctscrn0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/CScrn1.PNG",usertheme);
    vcmpctscrn1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/FScrn0.PNG",usertheme);
    vlargescrn0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Video/FScrn1.PNG",usertheme);
    vlargescrn1=insertpx(graphics);
    ////////////////////////SETTINGS
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Settings/Selection.PNG",usertheme);
    sttselection=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Settings/X0.PNG",usertheme);
    sttexit0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Settings/X1.PNG",usertheme);
    sttexit1=insertpx(graphics);
    ////////////////////////SETTINGS
    ////////////////////////MSG_WINDOWS
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/MsgFrames/X0.PNG",usertheme);
    msgexit0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/MsgFrames/X1.PNG",usertheme);
    msgexit1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/MsgFrames/Body.PNG",usertheme);
    msgbody=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/MsgFrames/B0.PNG",usertheme);
    msgbutton0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/MsgFrames/B1.PNG",usertheme);
    msgbutton1=insertpx(graphics);
    ////////////////////////MSG_WINDOWS
    //FOLDER PORTIONS///////
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Folders/X0.PNG",usertheme);
    fldexit0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Folders/X1.PNG",usertheme);
    fldexit1=insertpx(graphics);
    ////////////////////////PROGRAM ARROWS
    //TEXT
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Text/B0.PNG",usertheme);
    txtbck0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Text/B1.PNG",usertheme);
    txtbck1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Text/B2.PNG",usertheme);
    txtfwd0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/P.Text/B3.PNG",usertheme);
    txtfwd1=insertpx(graphics);
    //FOLDERS
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Folders/B0.PNG",usertheme);
    fldbck0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Folders/B1.PNG",usertheme);
    fldbck1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Folders/B2.PNG",usertheme);
    fldfwd0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/Folders/B3.PNG",usertheme);
    fldfwd1=insertpx(graphics);
    ////////////////////////PROGRAM ARROWS
    //////////////////////////////////////////THEMES
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/SystsemIcons/Wall0.png",usertheme);
    sttnwallpaper0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/SystsemIcons/Wall1.png",usertheme);
    sttnwallpaper1=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/SystsemIcons/Sttn0.png",usertheme);
    sttnsettings0=insertpx(graphics);
    sprintf(graphics,"ms0:/XT1-OS/System/Resources/Themes/%s/SystsemIcons/Sttn1.png",usertheme);
    sttnsettings1=insertpx(graphics);
    //////////////////////////////////////////THEMES
*/}
//loading of theme is finished <-- END FUNCTION''
//////////////////////
//CUSTOM SKINNING SYSTEM PREPERATIONS...
////////////////////////////////////////////////////////////////
//SYSTEM SIZING RESOLVE... BUILT FROM STRUCT THM. THEMESSS
//SYSTEM
thm.menu_width=fldexit0->imageWidth;
thm.menu_height=fldexit0->imageHeight;
//predefined////////////////////////*
thm.fullscreen_width=480;//PSP    //*
thm.fullscreen_height=272;//PSP   //*
////////////////////////////////////*
thm.folder_width=fldback0->imageWidth;
thm.folder_height=fldback1->imageHeight;
thm.battery_width=scrnbtry->imageWidth;
thm.battery_height=scrnbtry->imageHeight;
thm.time_width=scrntime->imageWidth;
thm.time_height=scrntime->imageHeight;
thm.files_width=Faud0->imageWidth;
thm.files_height=Faud0->imageHeight;
thm.startbutton_width=strt0->imageWidth;
thm.startbutton_height=strt0->imageHeight;
thm.startmenu_width=startbar->imageWidth;
thm.startmenu_height=startbar->imageHeight;
thm.startboard_width=strtl->imageWidth;
thm.startboard_height=strtl->imageHeight;
thm.startitem_width=browse0->imageWidth;
thm.startitem_height=browse0->imageHeight;
thm.cursor_width=scursor->imageWidth;
thm.cursor_height=scursor->imageHeight;
//MESSAGE BOX
thm.msgbox_width=msgbody->imageWidth;
thm.msgbox_height=msgbody->imageHeight;
thm.msgboxbtn_width=msgbutton0->imageWidth;
thm.msgboxbtn_height=msgbutton0->imageHeight;
//TEXT
//predefined///////////////////////////*
thm.font_width=8;                    //*
thm.font_height=8;                   //*
///////////////////////////////////////*
thm.twindow_width=txtback0->imageWidth;
thm.twindow_height=txtback0->imageHeight;
//MEDIA PLAYER
thm.mtopbar_width=audtop->imageWidth;
thm.mtopbar_height=audtop->imageHeight;
thm.mwindow_width=audwindow->imageWidth;
thm.mwindow_height=audwindow->imageHeight;
thm.mbutton_width=audplay0->imageWidth;
thm.mbutton_height=audplay0->imageHeight;
//********************************************\//ICONS
//CENTER SPACE VALUE*****\//
//set smallspacex for centering
//304 == compact folder pic width.// 304 was the original width of the folders during creation of this program so it's now replaced with thm.folder_width for theme purposes ;)
//SETUP ALL "X" VALUES
ico.round=thm.folder_width/ico.x;//int can't hold decimal places, so we get cleaned here ;)
// if round is not cleaned, the floating point is evaluated in the formula!!
ico.smallspacex=(thm.folder_width-(ico.x*ico.round)) / (ico.round);//(304%ico.x) should == 16 but it's ruined because for / we receive 6.3333-> so 
//\************************************************
ico.spacex=ico.spacex-(ico.spacex/(480/(ico.x+(ico.x/ico.splitx))));//(ico.x/ico.splitx)==spacex
//SETUP ALL "Y" VALUES
//(thm.folder_height-(thm.menu_height*2)) this equal folder width without counting menus
ico.round=(thm.folder_height-(thm.menu_height*2))/ico.y;
ico.smallspacey=((thm.folder_height-(thm.menu_height*2))-(ico.y*ico.round)) / (ico.round);
ico.spacey=ico.spacey-(ico.spacey/(272/(ico.y+(ico.y/ico.splity))));//(ico.y/ico.splity)==spacey
//********************************************\//ICONS
//COORDINATE SETUPS PROCEDURES//////////////////////////////////
//AUDIO
aud.x=thm.fullscreen_width-thm.mtopbar_width;
//TEXT
for(txt.count=0; txt.count<6; txt.count++)
                 {
                 txt.x[txt.count]=(thm.fullscreen_width-thm.twindow_width)/2;
                 txt.x[txt.count]=((thm.fullscreen_height-thm.startmenu_height)-thm.twindow_height)/2;
                 }
//DIRECTORIES... NONE, ALL ARE (0,0);
int audCenterScalingy=(thm.mtopbar_height-((thm.mtopbar_height/thm.mbutton_height)*thm.mbutton_height))/2;
int audCenterScalingx=thm.mtopbar_width-((thm.mtopbar_width/thm.mbutton_width)*thm.mbutton_width);
int EdgeAlign(int totalsize,int utilizedspace,int pieces)
{
    return(totalsize-((totalsize/utilizedspace)*utilizedspace))/pieces;
}//Y>>EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2);//X>>EdgeAlign(thm.mtopbar_width,thm.mbutton_width,1)
int ThemeCleaner(int totalsize,int utilizedspace,int pieces)
{
    return (totalsize-utilizedspace)/pieces;
}
//AUDIO HEIGHT ISSUES
//ThemeCleaner(thm.mtopbar_height,(thm.mtopbar_height/thm.mbutton_height)*thm.mbutton_height,2);
//AUDIO HEIGHT ISSUES
//ThemeCleaner(thm.mtopbar_width,(thm.mtopbar_width/thm.mbutton_width)*thm.mbutton_width,1);

////////////////////////////////////////////////////////////////
//**************************System Functions**********************************/

clearDebug();
pspDebugScreenSetTextColor(rgb(155,0,128));
dprint("Loading System Fuctions...");halt(9);
void FixControllerMode()
{
if(KrnlMode==1) sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
                else
if(KrnlMode==-1) sceCtrlSetSamplingMode(0);
if(ControllerRegion==-1){FIRSTCLICK=PSP_CTRL_CROSS;SECONDCLICK=PSP_CTRL_CIRCLE;}else{SECONDCLICK=PSP_CTRL_CROSS;FIRSTCLICK=PSP_CTRL_CIRCLE;}
}
//////////////////////

scePowerSetClockFrequency(222,222,111);
void ConvertProcessorPower()
{
     //remove XMB default processor level if program still crashes after system standby, not our standy... it doesn't crash
scePowerSetClockFrequency(222,222,111);
if(sttpower==-1){scePowerSetCpuClockFrequency(156);scePowerSetBusClockFrequency(111);}
else{scePowerSetCpuClockFrequency(158);scePowerSetBusClockFrequency(166);}
}

//////////////////////
void Call_Music()
{//music
char* codec; codec=strrchr(aud.currently_playing,'.');
if(stricmp(codec,".mp3")==0)
{//MP3
aud.isplaying=0;
////////////
MP3_Init(1);
MP3_Load(aud.currently_playingpth);
halt(3);
////////////
aud.ProgramsRunningC++;
sprintf(ProgramsRunning[ProgramsRunningC],"Audio");
MP3_Play();
aud.type=0;
}//MP3
/*else
if(stricmp(codec,".ogg")==0)
{//OGG
aud.isplaying=0;
////////////
OGG_Init(1);
OGG_Load(aud.currently_playingpth);
halt(3);
////////////
aud.ProgramsRunningC++;
sprintf(ProgramsRunning[ProgramsRunningC],"Audio");
OGG_Play();
aud.type=1;
}//OGG
*/
aud.isplaying=1;
}//music
void AudStatusRespond(){if(MP3_EndOfStream()==1){if(aud.style==1){Call_Music();} else if(aud.style==0){if(aud.type==0)MP3_Stop();/*else if(aud.type==1)OGG_Stop();*/aud.isplaying=-2;}}}
//////////////////////
////////////////////////////////////////////////:STANDBY MODE:
void PowerDown()
{
if(aud.isplaying==1){MP3_Pause();aud.resume_later=1;aud.isplaying=!aud.isplaying;}
fillScreenRect(rgb(0,0,0),0,0,thm.fullscreen_width,thm.fullscreen_height);
print(0,0,"Please turn the unit's screen off before",rgb(255,255,255));
print(0,15,"entering this mode for better results",rgb(255,255,255));
flipScreen();
          scePowerSetBusClockFrequency(8);scePowerSetCpuClockFrequency(9);
          //Damn... like this the system is practically dead lol :p
while(1)
{
        sceCtrlReadBufferPositive(&Controller,1);
          if((Controller.Buttons & PSP_CTRL_HOLD)==0)break;
}
ConvertProcessorPower();
if(aud.isplaying!=1&&aud.resume_later==1)Call_Music();
}
////////////////////////////////////////////////:STANDBY MODE:
//////////////////////
void Prepare_Depth(int altered,int increase)
{//begin function
     //types 0:folder,1:txt,etc...

if(d.depth>=-1)
{//allowed
for(d.count=altered; d.count>=0; d.count--)
                    {
for(counter=0; counter<=4; counter++)
{
     if(fld.depth[counter]==d.count){fld.depth[counter]=d.count+1;break;}
     else 
     if(txt.depth[counter]==d.count){txt.depth[counter]=d.count+1;break;}
}
                    }
if(increase>0)d.depth+=increase;
}//allowed
}//end function
void Repair_Depth(int altered2)
{//begin function
     //types 0:folder,1:txt,etc...
if(d.depth>-1)
{//forms exists
for(d.counter=altered2+1; d.counter<=d.depth; d.counter++)
{
     for(d.count=0; d.count<=4; d.count++)
                    {
     if(fld.depth[d.count]==d.counter){fld.depth[d.count]=d.counter-1;break;}
     else 
     if(txt.depth[d.count]==d.counter){txt.depth[d.count]=d.counter-1;break;}
                    }
}
d.depth--;
}//forms exists
}//end function
///////////
int Find_Open_Notepad()
{
 for(d.counter=0; d.counter<=4; d.counter++){if(txt.show[d.counter]!=1)return(d.counter);}
return 4;
}
////////
int Find_Open_Folder()
{
 for(d.counter=0; d.counter<=4; d.counter++){if(fld.show[d.counter]!=1)return(d.counter);}
return 4;
}
////////////
void Carry_Windows()
{
     if(aud.carry==1){if((aud.x==(cursor.x-aud.carryx) && aud.y==(cursor.y-aud.carryy))==0){aud.x=cursor.x-aud.carryx;aud.y=cursor.y-aud.carryy;}}
     for(wh.carry_count=0;wh.carry_count<=5;wh.carry_count++)
     {//WINDOW HANDLING CARRY INSPECTION LOOP<script>
     //TEXT INSPECTION
     if(txt.carry[wh.carry_count]==1 && wh.carry_count==txt.active)
     {
     if((txt.x[wh.carry_count]==(cursor.x-txt.carryx)&&txt.y[wh.carry_count]==(cursor.y-txt.carryy))==0)
     {txt.x[wh.carry_count]=cursor.x-txt.carryx;txt.y[wh.carry_count]=cursor.y-txt.carryy;}
     }
     //IMAGE INSPECTION
     
     //DIRECTORY INSPECTION
      if(fld.carry[wh.carry_count]==1 && wh.carry_count==fld.active)
     {
     if((fld.x[wh.carry_count]==(cursor.x-fld.carryx)&&fld.y[wh.carry_count]==(cursor.y-fld.carryy))==0)
     {fld.x[wh.carry_count]=cursor.x-fld.carryx;fld.y[wh.carry_count]=cursor.y-fld.carryy;}
     }
     }//WINDOW HANDLING CARRY INSPECTION LOOP</script>
//prevent errors//
//AUDIO REPAIRS*\//
if(aud.carry==1)
{//<--
if(aud.y>=272-4){aud.y=272-5;}
}//<--
//VIDEIO REPAIRS//
//DON'T NEED, THIS WILL BE UNECESSARY WITH THE AUTO HIDE START BAR
//TEXT REPAIRS**\//
//DON'T NEED, THIS WILL BE UNECESSARY WITH THE AUTO HIDE START BAR
//END REPAIRS***\//
}
//////////////////

////////////////////
void DrawAudio()
{
 if(aud.show == 1)
 {
    draw(0,0,thm.mtopbar_width,thm.mtopbar_height,audtop,aud.x,aud.y);
    if((/*_*/(cursor.y-aud.y)/thm.menu_height==0 && ((cursor.x-aud.x)-EdgeAlign(thm.mtopbar_width,thm.menu_width,1))/thm.menu_width==(thm.mtopbar_width/thm.menu_width)-1 && cursor.y>=aud.y)==0){draw(0,0,thm.menu_width,thm.menu_height,audexit0,aud.x+(thm.menu_width*((thm.mtopbar_width/thm.menu_width)-1))+EdgeAlign(thm.mtopbar_width,thm.menu_width,1),aud.y);} else{draw(0,0,thm.menu_width,thm.menu_height,audexit1,aud.x+(thm.menu_width*((thm.mtopbar_width/thm.menu_width)-1))+EdgeAlign(thm.mtopbar_width,thm.menu_width,1),aud.y);}//exit
    if((/*_*/(cursor.y-aud.y)/thm.menu_height==0 && (cursor.x-aud.x)/thm.menu_width==0 && cursor.x>=aud.x && cursor.y>=aud.y)==0){draw(0,0,thm.menu_width,thm.menu_height,audsizeswt0,aud.x,aud.y);} else{draw(0,0,thm.menu_width,thm.menu_height,audsizeswt1,aud.x,aud.y);}//window switcher
    if((/*_*/(((cursor.y-aud.y)-((((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height)))-EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2))/thm.mbutton_height==0 && (cursor.x-aud.x)/thm.mbutton_width==0 && cursor.x>=aud.x&&(cursor.y-aud.y)>=thm.menu_height*((thm.mtopbar_height/thm.menu_height)-1))==0){draw(0,0,thm.mbutton_width,thm.mbutton_height,audskpb0,aud.x+(thm.mbutton_width*0),(aud.y+(((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height))+EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2));} else{draw(0,0,thm.mbutton_width,thm.mbutton_height,audskpb1,aud.x+(thm.mbutton_width*0),(aud.y+(((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height))+EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2));}//back 
    if((/*_*/(((cursor.y-aud.y)-((((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height)))-EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2))/thm.mbutton_height==0 && (cursor.x-aud.x)/thm.mbutton_width==1&&(cursor.y-aud.y)>=thm.menu_height*((thm.mtopbar_height/thm.menu_height)-1))==0){draw(0,0,thm.mbutton_width,thm.mbutton_height,audskpf0,aud.x+(thm.mbutton_width*1),(aud.y+(((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height))+EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2));} else{draw(0,0,thm.mbutton_width,thm.mbutton_height,audskpf1,aud.x+(thm.mbutton_width*1),(aud.y+(((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height))+EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2));}//forward
    if((aud.isplaying)!=1){
    if(((cursor.x-aud.x)/thm.mbutton_width==2 && (((cursor.y-aud.y)-(+(((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height)))-EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2))/thm.mbutton_height==0&&(cursor.y-aud.y)>=thm.menu_height*((thm.mtopbar_height/thm.menu_height)-1))==0){draw(0,0,thm.mbutton_width,thm.mbutton_height,audplay0,aud.x+(thm.mbutton_width*2),(aud.y+(((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height))+EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2));} else{draw(0,0,thm.mbutton_width,thm.mbutton_height,audplay1,aud.x+(thm.mbutton_width*2),(aud.y+(((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height))+EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2));}
    }
    else
    {
    if(((cursor.x-aud.x)/thm.mbutton_width==2 && (((cursor.y-aud.y)-((((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height)))-EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2))/thm.mbutton_height==0&&(cursor.y-aud.y)>=thm.menu_height*((thm.mtopbar_height/thm.menu_height)-1))==0){draw(0,0,thm.mbutton_width,thm.mbutton_height,audpause0,aud.x+(thm.mbutton_width*2),(aud.y+(((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height))+EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2));} else{draw(0,0,thm.mbutton_width,thm.mbutton_height,audpause1,aud.x+(thm.mbutton_width*2),(aud.y+(((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height))+EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2));}
    }//play swith to pause if playing
    if(((cursor.x-aud.x)/thm.mbutton_width==3 && (((cursor.y-aud.y)-((((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height)))-EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2))/thm.mbutton_height==0&&(cursor.y-aud.y)>=thm.menu_height*((thm.mtopbar_height/thm.menu_height)-1))==0){draw(0,0,thm.mbutton_width,thm.mbutton_height,audstop0,aud.x+(thm.mbutton_width*3),(aud.y+(((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height))+EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2));} else{draw(0,0,thm.mbutton_width,thm.mbutton_height,audstop1,aud.x+(thm.mbutton_width*3),(aud.y+(((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height))+EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2));}//stop
    //draw(0,0,16,16,audtop,aud.x+(16*4),aud.y+16+1);//blank space 
    //draw(0,0,16,16,audtop,aud.x+(16*5),aud.y+16+1);//blank space
    if(aud.style!=1){if((/*_*/(((cursor.y-aud.y)-((((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height)))-EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2))/thm.mbutton_height==0 && ((cursor.x-aud.x)-EdgeAlign(thm.mtopbar_width,thm.mbutton_width,1))/thm.mbutton_width==((thm.mtopbar_width/thm.mbutton_width)-4)&&(cursor.y-aud.y)>=thm.menu_height*((thm.mtopbar_height/thm.menu_height)-1))==0){draw(0,0,thm.mbutton_width,thm.mbutton_height,audloop0,aud.x+(thm.mbutton_width*((thm.mtopbar_width/thm.mbutton_width)-4))+EdgeAlign(thm.mtopbar_width,thm.mbutton_width,1),(aud.y+(((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height))+EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2));}else{draw(0,0,thm.mbutton_width,thm.mbutton_height,audloop1,aud.x+(thm.mbutton_width*((thm.mtopbar_width/thm.mbutton_width)-4))+EdgeAlign(thm.mtopbar_width,thm.mbutton_width,1),(aud.y+(((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height))+EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2));}}else {draw(0,0,thm.mbutton_width,thm.mbutton_height,audloop2,aud.x+(thm.mbutton_width*((thm.mtopbar_width/thm.mbutton_width)-4))+EdgeAlign(thm.mtopbar_width,thm.mbutton_width,1),(aud.y+(((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height))+EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2));}//loop
    if(aud.style!=2){if((/*_*/(((cursor.y-aud.y)-((((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height)))-EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2))/thm.mbutton_height==0 && ((cursor.x-aud.x)-EdgeAlign(thm.mtopbar_width,thm.mbutton_width,1))/thm.mbutton_width==((thm.mtopbar_width/thm.mbutton_width)-3)&&(cursor.y-aud.y)>=thm.menu_height*((thm.mtopbar_height/thm.menu_height)-1))==0){draw(0,0,thm.mbutton_width,thm.mbutton_height,audshuff0,aud.x+(thm.mbutton_width*((thm.mtopbar_width/thm.mbutton_width)-3))+EdgeAlign(thm.mtopbar_width,thm.mbutton_width,1),(aud.y+(((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height))+EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2));}else {draw(0,0,thm.mbutton_width,thm.mbutton_height,audshuff1,aud.x+(thm.mbutton_width*((thm.mtopbar_width/thm.mbutton_width)-3))+EdgeAlign(thm.mtopbar_width,thm.mbutton_width,1),(aud.y+(((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height))+EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2));}}else {draw(0,0,thm.mbutton_width,thm.mbutton_height,audshuff2,aud.x+(thm.mbutton_width*((thm.mtopbar_width/thm.mbutton_width)-3))+EdgeAlign(thm.mtopbar_width,thm.mbutton_width,1),(aud.y+(((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height))+EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2));}//shuffle
    if(aud.style!=3){if((/*_*/(((cursor.y-aud.y)-((((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height)))-EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2))/thm.mbutton_height==0 && ((cursor.x-aud.x)-EdgeAlign(thm.mtopbar_width,thm.mbutton_width,1))/thm.mbutton_width==((thm.mtopbar_width/thm.mbutton_width)-2)&&(cursor.y-aud.y)>=thm.menu_height*((thm.mtopbar_height/thm.menu_height)-1))==0){draw(0,0,thm.mbutton_width,thm.mbutton_height,audcycle0,aud.x+(thm.mbutton_width*((thm.mtopbar_width/thm.mbutton_width)-2))+EdgeAlign(thm.mtopbar_width,thm.mbutton_width,1),(aud.y+(((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height))+EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2));}else {draw(0,0,thm.mbutton_width,thm.mbutton_height,audcycle1,aud.x+(thm.mbutton_width*((thm.mtopbar_width/thm.mbutton_width)-2))+EdgeAlign(thm.mtopbar_width,thm.mbutton_width,1),(aud.y+(((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height))+EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2));}}else {draw(0,0,thm.mbutton_width,thm.mbutton_height,audcycle2,aud.x+(thm.mbutton_width*((thm.mtopbar_width/thm.mbutton_width)-2))+EdgeAlign(thm.mtopbar_width,thm.mbutton_width,1),(aud.y+(((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height))+EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2));}//continue or next ooooohh... I just thought of a good one... "Cycle" nice huh ;)
    //draw(0,0,16,16,audtop,aud.x+(16*9),aud.y+16)+1;//blank space
    if(aud.size==1)
    {
    draw(0,0,thm.mwindow_width,thm.mwindow_height,audwindow,aud.x,aud.y+thm.mtopbar_height);//draw large mode window :)
    //THIS PREPARES AND DRAWS THE SONG CURRENTLY PLAYING IN LARGE AUDIO**********\//
    //THIS WILL BE MAID TO SCROLL AND SHOW THE ENTIRE NAME AND LOOP**************\//
    //sprintf(aud.dis_currently_playing,"Song: %s",aud.currently_playing);//\*******\//
    if(aud.isplaying==1)aud.lagspace=12; else aud.lagspace=0;
    if(aud.char_switch>=(25-aud.lagspace)&&aud.current_char+1<=(strlen(aud.currently_playing)+11))
    {
    aud.char_switch=0;aud.current_char++;
    }
    else
    {
    if(aud.current_char+1>strlen(aud.currently_playing)+11){aud.current_char=0;}
    }
    aud.char_switch++;
    for(aud.count=0; aud.count<=10; aud.count++)
    {
    if(aud.current_char-aud.count<0||aud.current_char-aud.count>strlen(aud.currently_playing))
    {aud.dis_currently_playing[16-aud.count]=' ';}
    else
    {aud.dis_currently_playing[16-aud.count]=aud.currently_playing[aud.current_char-aud.count];}
    }
    print(aud.x+1,(aud.y+thm.mtopbar_height)+(thm.mwindow_height-(8+2)),aud.dis_currently_playing,rgb(atoi(clr.red[2]),atoi(clr.grn[2]),atoi(clr.blu[2])));//
    //***************************************************************************\//
    }
 Carry_Windows();}
}
void DrawNotepad(int txtstart,int txtstop)
{
for(txt.count=txtstart; txt.count<=txtstop; txt.count++)
{//loop drawing
if(txt.show[txt.count]==1 && txt.fullscreen[txt.count]!=1)
{
 draw(0,0,thm.twindow_width,thm.twindow_height,txtback0,txt.x[txt.count],txt.y[txt.count]);
 print(txt.x[txt.count]+1,txt.y[txt.count]+thm.menu_height+((8*2)-thm.menu_height),"scroll:",rgb(atoi(clr.red[2]),atoi(clr.grn[2]),atoi(clr.blu[2])));
 //8*7 to push over and prevent "scroll:" to txt.scroll[] overlapping!!<--
 char show_scroll[36]; sprintf(show_scroll,"%i",txt.scroll[txt.count]);
 print((txt.x[txt.count]+1)+(8*7),txt.y[txt.count]+thm.menu_height+((8*2)-thm.menu_height),show_scroll,rgb(atoi(clr.red[2]),atoi(clr.grn[2]),atoi(clr.blu[2])));
int linerope=1;
 while(linerope<=(thm.twindow_height-(thm.menu_height+(8*2)))/(8*2)){print(txt.x[txt.count]+1,(txt.y[txt.count]+thm.menu_height)+((8*2)*linerope),txt.lines[linerope+(txt.count*(thm.fullscreen_height/(8*2)))],rgb(atoi(clr.red[0]),atoi(clr.grn[0]),atoi(clr.blu[0])));linerope++;}
//menu draws-->
if(((cursor.x-txt.x[txt.count])/thm.menu_width==0 && cursor.y>=txt.y[txt.count] && (cursor.y-txt.y[txt.count])/thm.menu_height==0)==0)draw(0,0,thm.menu_width,thm.menu_height,txtsizeswt0,txt.x[txt.count],txt.y[txt.count]);else draw(0,0,thm.menu_width,thm.menu_height,txtsizeswt1,txt.x[txt.count],txt.y[txt.count]);//size
if(( ((cursor.x-txt.x[txt.count])-EdgeAlign(thm.twindow_width,thm.menu_width,1))/thm.menu_width==((thm.twindow_width/thm.menu_width)-1) && cursor.y>=txt.y[txt.count] && (cursor.y-txt.y[txt.count])/thm.menu_height==0)==0)draw(0,0,thm.menu_width,thm.menu_height,txtexit0,(txt.x[txt.count]+(thm.menu_width*((thm.twindow_width/thm.menu_width)-1)))+EdgeAlign(thm.twindow_width,thm.menu_width,1),txt.y[txt.count]); else draw(0,0,thm.menu_width,thm.menu_height,txtexit1,(txt.x[txt.count]+(thm.menu_width*((thm.twindow_width/thm.menu_width)-1)))+EdgeAlign(thm.twindow_width,thm.menu_width,1),txt.y[txt.count]);//exit
if(((cursor.x-txt.x[txt.count])/thm.menu_width==((thm.twindow_width/thm.menu_width)-2) && (cursor.y-txt.y[txt.count])/thm.menu_height==1)==0)draw(0,0,thm.menu_width,thm.menu_height,txtbck0,txt.x[txt.count]+(thm.menu_width*((thm.twindow_width/thm.menu_width)-2)),txt.y[txt.count]+(thm.menu_height*1));else draw(0,0,thm.menu_width,thm.menu_height,txtbck1,txt.x[txt.count]+(thm.menu_width*((thm.twindow_width/thm.menu_width)-2)),txt.y[txt.count]+(thm.menu_height*1));//back
if(((cursor.x-txt.x[txt.count])/thm.menu_width==((thm.twindow_width/thm.menu_width)-1) && (cursor.y-txt.y[txt.count])/thm.menu_height==1)==0)draw(0,0,thm.menu_width,thm.menu_height,txtfwd0,txt.x[txt.count]+(thm.menu_width*((thm.twindow_width/thm.menu_width)-1)),txt.y[txt.count]+(thm.menu_height*1));else draw(0,0,thm.menu_width,thm.menu_height,txtfwd1,txt.x[txt.count]+(thm.menu_width*((thm.twindow_width/thm.menu_width)-1)),txt.y[txt.count]+(thm.menu_height*1));//forw

Carry_Windows();
}//end positive show response~
}//end draw loop!
}//end function

void DrawFolder(int startpoint, int stopbefore)
{
   Carry_Windows();
     for(fld.counter=startpoint; fld.counter<=stopbefore; fld.counter++)
     {
     if(fld.show[fld.counter]==1)
     {
     draw(0,0,304,176,fldback0,fld.x[fld.counter],fld.y[fld.counter]);
     print(fld.x[fld.counter]+1,(fld.y[fld.counter]+thm.menu_height)+(8/2),fld2.dis_dir[fld.counter],rgb(atoi(clr.red[3]),atoi(clr.grn[3]),atoi(clr.blu[3])));
     //the minus -1 is because the folder back has 2 extra pixels for a left and right border the another extra for the bottom border but x doesn't need to check the bottom and it doesn't affect the y status for our checking since it's all the way at the bottom and out of our way...
     if(cursor.x>fld.x[fld.counter]&&cursor.y>=fld.y[fld.counter]&&((cursor.x-fld.x[fld.counter])-EdgeAlign(thm.folder_width,thm.menu_width,1))/thm.menu_width==(304/thm.menu_width)-1&&(cursor.y-fld.y[fld.counter])/thm.menu_height==0)draw(0,0,thm.menu_width,thm.menu_height,fldexit1,(fld.x[fld.counter]+(thm.menu_width*((304/thm.menu_width)-1)))+EdgeAlign(thm.folder_width,thm.menu_width,1),fld.y[fld.counter]);else draw(0,0,thm.menu_width,thm.menu_height,fldexit0,(fld.x[fld.counter]+(thm.menu_width*((304/thm.menu_width)-1)))+EdgeAlign(thm.folder_width,thm.menu_width,1),fld.y[fld.counter]);
     if(cursor.x>=fld.x[fld.counter]&&cursor.y>=fld.y[fld.counter]&&(cursor.x-fld.x[fld.counter])/thm.menu_width==0&&(cursor.y-fld.y[fld.counter])/thm.menu_height==0)draw(0,0,thm.menu_width,thm.menu_height,fldsizeswt1,fld.x[fld.counter],fld.y[fld.counter]);else draw(0,0,thm.menu_width,thm.menu_height,fldsizeswt0,fld.x[fld.counter],fld.y[fld.counter]);
     if(cursor.x>fld.x[fld.counter]&&(cursor.x-fld.x[fld.counter])/thm.menu_width==(304/thm.menu_width)-2&&(cursor.y-fld.y[fld.counter])/thm.menu_height==1)draw(0,0,thm.menu_width,thm.menu_height,fldbck1,fld.x[fld.counter]+(thm.menu_width*((304/thm.menu_width)-2)),fld.y[fld.counter]+(thm.menu_height*1));else draw(0,0,thm.menu_width,thm.menu_height,fldbck0,fld.x[fld.counter]+(thm.menu_width*((304/thm.menu_width)-2)),fld.y[fld.counter]+(thm.menu_height*1));
     if(cursor.x>fld.x[fld.counter]&&(cursor.x-fld.x[fld.counter])/thm.menu_width==(304/thm.menu_width)-1&&(cursor.y-fld.y[fld.counter])/thm.menu_height==1)draw(0,0,thm.menu_width,thm.menu_height,fldfwd1,fld.x[fld.counter]+(thm.menu_width*((304/thm.menu_width)-1)),fld.y[fld.counter]+(thm.menu_height*1));else draw(0,0,thm.menu_width,thm.menu_height,fldfwd0,fld.x[fld.counter]+(thm.menu_width*((304/thm.menu_width)-1)),fld.y[fld.counter]+(thm.menu_height*1));
     //
     ///draw contained materials
     //int span=0;
     //while(span<16)
     //{//while
     for(fld.column=0;fld.column<304/ico.x;fld.column++)
     {
     for(fld.file_count=0;fld.file_count<(176-(thm.menu_height*2))/ico.y;fld.file_count++)
     {
      if(fld.file[((fld.column*((176-(thm.menu_height*2))/ico.y))+fld.file_count)+(fld.counter*33)][0]!='\0')
      {//instance exists
      if(fld.format[((fld.column*((176-(thm.menu_height*2))/ico.y))+fld.file_count)+(fld.counter*33)]==0)
      {
if((cursor.x-fld.x[fld.counter]>=ico.smallspacex+(ico.smallspacex*fld.column)&&((cursor.x-fld.x[fld.counter])-(ico.smallspacex+(ico.smallspacex*fld.column)))/ico.x==(fld.column*1)&&((cursor.y-fld.y[fld.counter])-(thm.menu_height*2))/ico.y==fld.file_count&&(cursor.y-fld.y[fld.counter])>=thm.menu_height*2)==0)
      draw(0,0,ico.x,ico.y,Funk0,(fld.x[fld.counter]+(fld.column*ico.x))+(ico.smallspacex+(ico.smallspacex*fld.column)),fld.y[fld.counter]+((fld.file_count*ico.y)+(thm.menu_height*2)));
      else
      draw(0,0,ico.x,ico.y,Funk1,(fld.x[fld.counter]+(fld.column*ico.x))+(ico.smallspacex+(ico.smallspacex*fld.column)),fld.y[fld.counter]+((fld.file_count*ico.y)+(thm.menu_height*2)));
      }else
      if(fld.format[((fld.column*((176-(thm.menu_height*2))/ico.y))+fld.file_count)+(fld.counter*33)]==1)
      {
if((cursor.x-fld.x[fld.counter]>=ico.smallspacex+(ico.smallspacex*fld.column)&&((cursor.x-fld.x[fld.counter])-(ico.smallspacex+(ico.smallspacex*fld.column)))/ico.x==(fld.column*1)&&((cursor.y-fld.y[fld.counter])-(thm.menu_height*2))/ico.y==fld.file_count&&(cursor.y-fld.y[fld.counter])>=thm.menu_height*2)==0)
      draw(0,0,ico.x,ico.y,folder0,(fld.x[fld.counter]+(fld.column*ico.x))+(ico.smallspacex+(ico.smallspacex*fld.column)),fld.y[fld.counter]+((fld.file_count*ico.y)+(thm.menu_height*2)));
      else
      draw(0,0,ico.x,ico.y,folder1,(fld.x[fld.counter]+(fld.column*ico.x))+(ico.smallspacex+(ico.smallspacex*fld.column)),fld.y[fld.counter]+((fld.file_count*ico.y)+(thm.menu_height*2)));
      }
      else
      if(fld.format[((fld.column*((176-(thm.menu_height*2))/ico.y))+fld.file_count)+(fld.counter*33)]==2)
      {
if((cursor.x-fld.x[fld.counter]>=ico.smallspacex+(ico.smallspacex*fld.column)&&((cursor.x-fld.x[fld.counter])-(ico.smallspacex+(ico.smallspacex*fld.column)))/ico.x==(fld.column*1)&&((cursor.y-fld.y[fld.counter])-((thm.menu_height*2)+(ico.smallspacey+(ico.smallspacey*fld.file_count))))/ico.y==fld.file_count&&(cursor.y-fld.y[fld.counter])>=thm.menu_height*2)==0)
      draw(0,0,ico.x,ico.y,Faud0,(fld.x[fld.counter]+(fld.column*ico.x))+(ico.smallspacex+(ico.smallspacex*fld.column)),fld.y[fld.counter]+((fld.file_count*ico.y)+(thm.menu_height*2)+(ico.smallspacey+(ico.smallspacey*fld.file_count))));
      else
      draw(0,0,ico.x,ico.y,Faud1,(fld.x[fld.counter]+(fld.column*ico.x))+(ico.smallspacex+(ico.smallspacex*fld.column)),fld.y[fld.counter]+((fld.file_count*ico.y)+(thm.menu_height*2)+(ico.smallspacey+(ico.smallspacey*fld.file_count))));
      }else
      if(fld.format[((fld.column*((176-(thm.menu_height*2))/ico.y))+fld.file_count)+(fld.counter*33)]==3)
      {
if((cursor.x-fld.x[fld.counter]>=ico.smallspacex+(ico.smallspacex*fld.column)&&((cursor.x-fld.x[fld.counter])-(ico.smallspacex+(ico.smallspacex*fld.column)))/ico.x==(fld.column*1)&&((cursor.y-fld.y[fld.counter])-(thm.menu_height*2))/ico.y==fld.file_count&&(cursor.y-fld.y[fld.counter])>=thm.menu_height*2)==0)
      draw(0,0,ico.x,ico.y,Fpic0,(fld.x[fld.counter]+(fld.column*ico.x))+(ico.smallspacex+(ico.smallspacex*fld.column)),fld.y[fld.counter]+((fld.file_count*ico.y)+(thm.menu_height*2)));
      else
      draw(0,0,ico.x,ico.y,Fpic1,(fld.x[fld.counter]+(fld.column*ico.x))+(ico.smallspacex+(ico.smallspacex*fld.column)),fld.y[fld.counter]+((fld.file_count*ico.y)+(thm.menu_height*2)));
      }else
      if(fld.format[((fld.column*((176-(thm.menu_height*2))/ico.y))+fld.file_count)+(fld.counter*33)]==4)
      {
if((cursor.x-fld.x[fld.counter]>=ico.smallspacex+(ico.smallspacex*fld.column)&&((cursor.x-fld.x[fld.counter])-(ico.smallspacex+(ico.smallspacex*fld.column)))/ico.x==(fld.column*1)&&((cursor.y-fld.y[fld.counter])-(thm.menu_height*2))/ico.y==fld.file_count&&(cursor.y-fld.y[fld.counter])>=thm.menu_height*2)==0)
      draw(0,0,ico.x,ico.y,Ftxt0,(fld.x[fld.counter]+(fld.column*ico.x))+(ico.smallspacex+(ico.smallspacex*fld.column)),fld.y[fld.counter]+((fld.file_count*ico.y)+(thm.menu_height*2)));
      else
      draw(0,0,ico.x,ico.y,Ftxt1,(fld.x[fld.counter]+(fld.column*ico.x))+(ico.smallspacex+(ico.smallspacex*fld.column)),fld.y[fld.counter]+((fld.file_count*ico.y)+(thm.menu_height*2)));
      }else
      if(fld.format[((fld.column*((176-(thm.menu_height*2))/ico.y))+fld.file_count)+(fld.counter*33)]==5)
      {
if((cursor.x-fld.x[fld.counter]>=ico.smallspacex+(ico.smallspacex*fld.column)&&((cursor.x-fld.x[fld.counter])-(ico.smallspacex+(ico.smallspacex*fld.column)))/ico.x==(fld.column*1)&&((cursor.y-fld.y[fld.counter])-(thm.menu_height*2))/ico.y==fld.file_count&&(cursor.y-fld.y[fld.counter])>=thm.menu_height*2)==0)
      draw(0,0,ico.x,ico.y,Fpbp0,(fld.x[fld.counter]+(fld.column*ico.x))+(ico.smallspacex+(ico.smallspacex*fld.column)),fld.y[fld.counter]+((fld.file_count*ico.y)+(thm.menu_height*2)));
      else
      draw(0,0,ico.x,ico.y,Fpbp1,(fld.x[fld.counter]+(fld.column*ico.x))+(ico.smallspacex+(ico.smallspacex*fld.column)),fld.y[fld.counter]+((fld.file_count*ico.y)+(thm.menu_height*2)));
      }
      print((fld.x[fld.counter]+(fld.column*ico.x))+(ico.smallspacex+(ico.smallspacex*fld.column)),(fld.y[fld.counter]+(ico.y-8))+((fld.file_count*ico.y)+(thm.menu_height*2)),fld2.dis_file[(((fld.column*((176-(thm.menu_height*2))/ico.y))+fld.file_count))+(fld.counter*33)],rgb(atoi(clr.red[4]),atoi(clr.grn[4]),atoi(clr.blu[4])));
      }//instance exists
     }                                                
     }
     //span++;
     //}//while
     ///////////////////////////
     }
     }
}
//////////////////////////////
void DrawWallpaper()
{
     draw(0,0,thm.fullscreen_width,thm.fullscreen_height,bgpic,0,0);
}
void FreeUserTheme()
{
openfile = sceIoOpen("ms0:/XT1-OS/System/Structure/Theme",PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC,0);
sceIoLseek(openfile,0,SEEK_SET);
sceIoWrite (openfile,sd.file[(sd.counter+(sd.column*4))],strlen(sd.file[(sd.counter+(sd.column*4))]));
sceIoClose (openfile);
//scePowerSetClockFrequency(222,222,111);//try to prevent crash...
Read_User_Theme();
Unload_Theme();
Load_Theme();
}
void FreeWallpaper(char *DesiredWallpaper)
{
openfile = sceIoOpen("ms0:/XT1-OS/System/Structure/Wallpaper",PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC,0);
sceIoLseek(openfile,0,SEEK_SET);
sceIoWrite (openfile,DesiredWallpaper,strlen(DesiredWallpaper));
sceIoClose (openfile);
freeImage(bgpic);
sprintf(graphics,"ms0:/XT1-OS/System/Resources/Wallpaper/%s",DesiredWallpaper);
bgpic=insertpx(graphics);
}
void DrawDesktop()
{
//fillScreenRect(rgb(0,68,136),0,0,thm.fullscreen_width,thm.fullscreen_height);//incase no wallpaper is there :p
    DrawWallpaper();
//call program drawings here so startmenu covers them
/////////////////////////////////////////////////////*
if(d.depth>-1)                                     //*
{//there really is something to draw!!             //*
for(d.count=d.depth; d.count>=0; d.count--)        //*
{//loopzz                                          //*
for(d.counter=4;d.counter>=0; d.counter--)         //*
{//loopyy                                          //*
if(txt.depth[d.counter]==d.count&&txt.show[d.counter]==1)
{DrawNotepad(d.counter,d.counter);break;}          //*
else                                               //*
if(fld.depth[d.counter]==d.count&&fld.show[d.counter]==1)
{DrawFolder(d.counter,d.counter);break;}           //*
}//loopyy                                          //*
}//loopzz                                          //*
}//there really is something to draw!!             //*
DrawAudio();                                       //*
/////////////////////////////////////////////////////*
    draw(0,0,thm.fullscreen_width,18,startbar,0,thm.fullscreen_height-18);
    //draw start features :)
    if(Start==-1){
    if(cursor.x<=84 && cursor.y>=thm.fullscreen_height-thm.startbutton_height)
    draw(0,0,thm.startbutton_width,thm.startbutton_height,strt1,0,thm.fullscreen_height-thm.startbutton_height);else draw(0,0,thm.startbutton_width,thm.startbutton_height,strt0,0,thm.fullscreen_height-thm.startbutton_height);
    }
    else{
    draw(0,0,184,231,strtl,0,thm.fullscreen_height-249);
    if(cursor.x<132 && cursor.y<thm.fullscreen_height-(18+2) && cursor.y>=34)
    draw(0,0,132,13,select,0,thm.fullscreen_height-((lround((cursor.y-264)*(-1)/13)*13.0769)+(18)));//13.0769 because it needs to be + 1 to keep it from getting distorted since there are no gaps :) 1/3=.0769;I Love Math!!:)
//print start list *note* this was created above inside the start function to avoid errors during development, move it back if necessary...
for(counter=16; counter>=0; counter--)
{
sprintf(SMenu,"%s",start.dis_item[counter]);
if(counter!=16)
print(0,thm.fullscreen_height-round((counter+2)*13.0769),SMenu,rgb(atoi(clr.red[1]),atoi(clr.grn[1]),atoi(clr.blu[1])));
else
print(0,thm.fullscreen_height-round((counter+2)*13.0769),SMenu,rgb(atoi(clr.red[3]),atoi(clr.grn[3]),atoi(clr.blu[3])));
}
if(((cursor.y-16)/31==1 && cursor.x>=132 && cursor.x<=183)==0){draw(0,0,50,20,browse0,184-51,(16+(31*1)));}else {draw(0,0,50,20,browse1,184-51,(16+(31*1)));}//button coulumn 1//system browse
if(((cursor.y-16)/31==2 && cursor.x>=132 && cursor.x<=183)==0){draw(0,0,50,20,setting0,184-51,(16+(31*2)));}else {draw(0,0,50,20,setting1,184-51,(16+(31*2)));}//button coulumn 2//system settings
if(((cursor.y-16)/31==3 && cursor.x>=132 && cursor.x<=183)==0){draw(0,0,50,20,themes0,184-51,(16+(31*3)));}else {draw(0,0,50,20,themes1,184-51,(16+(31*3)));}//button coulumn 1//system themes
if(((cursor.y-16)/31==7 && cursor.x>=132 && cursor.x<=183)==0){draw(0,0,50,20,startexit0,184-51,(16+(31*7)));}else {draw(0,0,50,20,startexit1,184-51,(16+(31*7)));}//button coulumn 3//system shutdown
    draw(0,0,thm.startbutton_width,thm.startbutton_height,strt2,0,thm.fullscreen_height-thm.startbutton_height);
    }
    //print(0,0,"XT1-OS : by Devun_06 shouts out to my boys M.M.M.>Nelle>Kyle",rgb(0,0,168));
    //print(0,10,"Denby:Mr.Hawk,Golighty: Mr.Ware, and all my other friends.",rgb(0,0,168));
    //draw information for debug here :)
}//end function
//////////////////////


void DrawBattery()
{
    if(scePowerIsBatteryExist())
    {
    if(scePowerGetBatteryLifePercent()>=90)draw(0,0,23,18,b0,thm.fullscreen_width-66,thm.fullscreen_height-18);
                                else
    if(scePowerGetBatteryLifePercent()>=80)draw(0,0,23,18,b1,thm.fullscreen_width-66,thm.fullscreen_height-18);
                                else
    if(scePowerGetBatteryLifePercent()>=70)draw(0,0,23,18,b2,thm.fullscreen_width-66,thm.fullscreen_height-18);
                                else
    if(scePowerGetBatteryLifePercent()>=60)draw(0,0,23,18,b3,thm.fullscreen_width-66,thm.fullscreen_height-18);
                                else
    if(scePowerGetBatteryLifePercent()>=50)draw(0,0,23,18,b4,thm.fullscreen_width-66,thm.fullscreen_height-18);
                                else
    if(scePowerGetBatteryLifePercent()>=40)draw(0,0,23,18,b5,thm.fullscreen_width-66,thm.fullscreen_height-18);
                                else
    if(scePowerGetBatteryLifePercent()>=30)draw(0,0,23,18,b6,thm.fullscreen_width-66,thm.fullscreen_height-18);
                                else
    if(scePowerGetBatteryLifePercent()>=20)draw(0,0,23,18,b7,thm.fullscreen_width-66,thm.fullscreen_height-18);
                                else 
    if(scePowerGetBatteryLifePercent()>=10)draw(0,0,23,18,b8,thm.fullscreen_width-66,thm.fullscreen_height-18);
                                else
                                draw(0,0,23,18,b9,thm.fullscreen_width-66,thm.fullscreen_height-18);
    }else{draw(0,0,23,18,bchrg,thm.fullscreen_width-66,thm.fullscreen_height-18);}
        if(DesktopFeatures==2){
                           //int and display initiated time values!!                       
                          sprintf(DesktopFeaturesData0,"  Battery");
                          sprintf(DesktopFeaturesData1,"%i%%",scePowerGetBatteryLifePercent());
                          sprintf(DesktopFeaturesData2,"%i:%02d",scePowerGetBatteryLifeTime()/60,scePowerGetBatteryLifeTime()%60);
                          if(scePowerIsBatteryCharging()==1)sprintf(DesktopFeaturesData3,"Charging");
                          else 
                          if(scePowerIsBatteryExist()==0)sprintf(DesktopFeaturesData3,"Removed");
                          else 
                          sprintf(DesktopFeaturesData3,"Normal");
                          draw(0,0,thm.battery_width,thm.battery_height,scrnbtry,thm.fullscreen_width-thm.battery_width,thm.fullscreen_height-(thm.startmenu_height+thm.battery_height));
                          print(thm.fullscreen_width-(thm.battery_width-3),thm.fullscreen_height-92,DesktopFeaturesData0,rgb(atoi(clr.red[3]),atoi(clr.grn[3]),atoi(clr.blu[3])));
                          print(thm.fullscreen_width-(thm.battery_width-3),thm.fullscreen_height-72,"Percent%",rgb(atoi(clr.red[2]),atoi(clr.grn[2]),atoi(clr.blu[2])));
                          //print(thm.fullscreen_width-(8*((scePowerGetBatteryLifePercent()/10)+2)),thm.fullscreen_height-72,DesktopFeaturesData1,rgb(atoi(clr.red[2]),atoi(clr.grn[2]),atoi(clr.blu[2])));
                          print(thm.fullscreen_width-(8*strlen(DesktopFeaturesData1)),thm.fullscreen_height-72,DesktopFeaturesData1,rgb(atoi(clr.red[2]),atoi(clr.grn[2]),atoi(clr.blu[2])));
                          print(thm.fullscreen_width-(thm.battery_width-3),thm.fullscreen_height-62,"TimeLeft:",rgb(atoi(clr.red[2]),atoi(clr.grn[2]),atoi(clr.blu[2])));
                          print(thm.fullscreen_width-(8*strlen(DesktopFeaturesData2)),thm.fullscreen_height-62,DesktopFeaturesData2,rgb(atoi(clr.red[2]),atoi(clr.grn[2]),atoi(clr.blu[2])));
                          //print(thm.fullscreen_width-(thm.battery_width-3),thm.fullscreen_height-140,DesktopFeaturesData3,rgb(255,255,255));
                          //print(thm.fullscreen_width-(thm.battery_width-3),thm.fullscreen_height-85,DesktopFeaturesData4,rgb(255,255,255));
                          print(thm.fullscreen_width-(thm.battery_width-3),thm.fullscreen_height-27,"Status:",rgb(atoi(clr.red[2]),atoi(clr.grn[2]),atoi(clr.blu[2])));
                          print(thm.fullscreen_width-(8*strlen(DesktopFeaturesData3)),thm.fullscreen_height-(thm.startmenu_height+8+1),DesktopFeaturesData3,rgb(atoi(clr.red[2]),atoi(clr.grn[2]),atoi(clr.blu[2])));
                          }
}
//////////////////////


void DrawTime()
{
    struct tm *TimeNow;
    time_t psclock;
    sceKernelLibcTime(&psclock);
    TimeNow = gmtime(&psclock);
    sceKernelLibcTime(&psclock);//used &psptime so it can let sceKernelLibcTime set it to the 1970 epoch time in seconds.
    strftime(time,10,"%H:%M",TimeNow);
    sprintf(time,"%02d:%02d",(TimeNow->tm_hour+12>12?((TimeNow->tm_hour+12)-((TimeNow->tm_hour/13)*12))-5:12),TimeNow->tm_min); 
    print(439,thm.fullscreen_height-13,time,rgb(atoi(clr.red[5]),atoi(clr.grn[5]),atoi(clr.blu[5])));
    if(DesktopFeatures==1){
                           //int and display initiated time values!!                       
                          strftime(DesktopFeaturesData0,30,"  %B",TimeNow);
                          strftime(DesktopFeaturesData1,30,"%a,%d",TimeNow);
                          strftime(DesktopFeaturesData2,30,"%j/366",TimeNow);
                          //DesktopFeaturesData6=(int)(TimeNow->tm_yday/7);
                          //sprintf(DesktopFeaturesData3,"Weeks:           %i",TimeNow->tm_yday/7);
                          //there is no desktop 4 feature for time so don't activate the printing of it currently set as a comment!!//Now with the skin compatible window version... #4 is in use ;)
                          strftime(DesktopFeaturesData4,30,"%Y",TimeNow);
                          strftime(DesktopFeaturesData5,30,"%I:%M.%S",TimeNow);
                          draw(0,0,thm.time_width,thm.time_height,scrntime,thm.fullscreen_width-thm.time_width,thm.fullscreen_height-(thm.time_height+thm.startmenu_height));
                          print(thm.fullscreen_width-(thm.time_width-3),thm.fullscreen_height-130,DesktopFeaturesData0,rgb(atoi(clr.red[3]),atoi(clr.grn[3]),atoi(clr.blu[3])));
                          print(thm.fullscreen_width-(thm.time_width-3),thm.fullscreen_height-100,"Today:",rgb(atoi(clr.red[2]),atoi(clr.grn[2]),atoi(clr.blu[2])));
                          print(thm.fullscreen_width-(8*strlen(DesktopFeaturesData1)),thm.fullscreen_height-100,DesktopFeaturesData1,rgb(atoi(clr.red[2]),atoi(clr.grn[2]),atoi(clr.blu[2])));
                          print(thm.fullscreen_width-(thm.time_width-3),thm.fullscreen_height-82,"Year#:",rgb(atoi(clr.red[2]),atoi(clr.grn[2]),atoi(clr.blu[2])));
                          print(thm.fullscreen_width-(8*strlen(DesktopFeaturesData2)),thm.fullscreen_height-82,DesktopFeaturesData2,rgb(atoi(clr.red[2]),atoi(clr.grn[2]),atoi(clr.blu[2])));
                          //print(thm.fullscreen_width-(thm.time_width-3),thm.fullscreen_height-140,DesktopFeaturesData3,rgb(255,255,255));
                          //print(thm.fullscreen_width-(thm.time_width-3),thm.fullscreen_height-85,DesktopFeaturesData4,rgb(255,255,255));
                          print(thm.fullscreen_width-(thm.time_width-3),thm.fullscreen_height-27,DesktopFeaturesData4,rgb(atoi(clr.red[2]),atoi(clr.grn[2]),atoi(clr.blu[2])));
                          print(thm.fullscreen_width-(8*strlen(DesktopFeaturesData5)),thm.fullscreen_height-(thm.startmenu_height+8+1),DesktopFeaturesData5,rgb(atoi(clr.red[2]),atoi(clr.grn[2]),atoi(clr.blu[2])));
                          }
}
//////////////////////
void DrawCursor()
{
     if(RepairLag==1)
     {
     if(aud.isplaying==1)cursor.lag++;
     //next
     if(Start==1&&aud.isplaying==1)cursor.lag=2;
     //next
     if(d.depth>-1&&Desktop==1){cursor.lag=cursor.lag+((d.depth+1))/2;}
     
     //plus one cause -1 == none running 0 ==1 etc...
     }
     if(KrnlMode==1)
     {
//divide by 32 so it's not active unless its greater prevents super sensitivity :)
      cursor.x+=(int)(((Controller.Lx-128)/46)*(cursor.speed+cursor.lag));
      cursor.y+=(int)(((Controller.Ly-128)/46)*(cursor.speed+cursor.lag));
     }
     else
     if(KrnlMode==-1)
     {
                    if(Controller.Buttons & PSP_CTRL_LEFT)cursor.x-=(cursor.speed+1)+cursor.lag;
                    if(Controller.Buttons & PSP_CTRL_RIGHT)cursor.x+=(cursor.speed+1)+cursor.lag;
                    if(Controller.Buttons & PSP_CTRL_UP)cursor.y-=(cursor.speed+1)+cursor.lag;
                    if(Controller.Buttons & PSP_CTRL_DOWN)cursor.y+=(cursor.speed+1)+cursor.lag;
     }
//keeps the cursor from retardedly going too far off the d@mn screen lol :) Devun_06*
if(cursor.x<0)cursor.x=0;
if(cursor.y<0)cursor.y=0;
if(cursor.x>479)cursor.x=479;//instead of implying major math here keep it
if(cursor.y>271)cursor.y=271;//lame so it can be easy to expand upon...
cursor.lag=0;//incase the lag was altered we recover it here. If it needs to change, it can do so upon restart or the function ;)
draw(0,0,thm.cursor_width,thm.cursor_height,scursor,cursor.x,cursor.y);
if(StopPowerSave==1){scePowerTick(0);}//I don't know if this works but I'm trying :D this don't work in standby cause I want it to do powersave there.
         //Check Hold
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if(Controller.Buttons & PSP_CTRL_HOLD){if(Standby==1){PowerDown();}                                              //
else                                                                                                             //
{print((thm.fullscreen_width/2)-(8*4),((thm.fullscreen_height-thm.startmenu_height)/2)+(8/2),"-Locked-",rgb(atoi(clr.red[6]),atoi(clr.grn[6]),atoi(clr.blu[6])));}}   //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////

int DisplayMsgbox()
{
    //halt(14);
    if(Desktop==0){flipScreen();Screenshot("ms0:/XT1-OS/System/Structure/System Resources/Form0.png");
    sprintf(graphics,"ms0:/XT1-OS/System/Structure/System Resources/Form0.png");}
    systemform0=insertpx(graphics);
while(1)
{
        sceCtrlReadBufferPositive(&Controller,1);
        //ATTEMPT TO MAKE OS APPEAR TO BE ACTIVE//BEGIN
        if(Desktop==1){DrawDesktop();DrawBattery();DrawTime();}else{draw(0,0,thm.fullscreen_width,thm.fullscreen_height,systemform0,0,0);}//first line taken from main loop.//
        //ATTEMPT TO MAKE OS APPEAR TO BE ACTIVE//DONE!
        if(msg.carry==1){msg.x=cursor.x-msg.carryx;msg.y=cursor.y-msg.carryy;}
        if((Controller.Buttons & FIRSTCLICK)==0)msg.carry=0;
        draw(0,0,thm.msgbox_width,thm.msgbox_height,msgbody,msg.x,msg.y);
        print(msg.x+1,msg.y+(8/2),msg.title,rgb(atoi(clr.red[3]),atoi(clr.grn[3]),atoi(clr.blu[3])));
        //print(msg.x+2,msg.y+20,msg.message,rgb(atoi(clr.red[0]),atoi(clr.grn[0]),atoi(clr.blu[0])));
        int msg_barrier=(thm.msgbox_width/8)-1;
        //**480 == psp fullscreen width**\//
        //msglines are [60] because 480/8 == 60 and 480 is the PSP screen's actual width... ;) +1 for holding the newline char<-
        char msgline1[61];
        char msgline2[61];
        char msgline3[61];
        //prepare for initiation and per use
        msgline1[0]='\0';
        msgline2[0]='\0';
        msgline3[0]='\0';
        sprintf(msgline1,"%s",msg.message);
        if(strlen(msg.message)/((thm.msgbox_width/8)-1)>=1){sprintf(msgline2,"%s",msg.message+(msg_barrier));}
        if(strlen(msg.message)/((thm.msgbox_width/8)-1)==2){sprintf(msgline3,"%s",msg.message+(msg_barrier*2));}
        msgline1[msg_barrier]='\0';//clear ending
        msgline2[msg_barrier]='\0';//clear ending
        msgline3[msg_barrier]='\0';//clear ending
        print(msg.x+2,msg.y+thm.menu_height+3+((8+1)*0),msgline1,rgb(atoi(clr.red[0]),atoi(clr.grn[0]),atoi(clr.blu[0])));
        print(msg.x+2,msg.y+thm.menu_height+3+((8+1)*1),msgline2,rgb(atoi(clr.red[0]),atoi(clr.grn[0]),atoi(clr.blu[0])));
        print(msg.x+2,msg.y+thm.menu_height+3+((8+1)*2),msgline3,rgb(atoi(clr.red[0]),atoi(clr.grn[0]),atoi(clr.blu[0])));
        //fix button coordinates*\//////////////////////////////////////////////
        if(msg.type==1)msg.bx=(thm.msgbox_width/2)-(thm.msgboxbtn_width/2);
        else 
        msg.bx=(thm.msgbox_width-(thm.msgboxbtn_width*2))/4;
        msg.by=thm.menu_height+((((thm.msgbox_height-thm.menu_height)/thm.msgboxbtn_height)-1)*thm.msgboxbtn_height)+EdgeAlign(thm.msgbox_height,thm.msgboxbtn_height,3);
        msg.bttntext0=(msg.x+msg.bx+(thm.msgboxbtn_width/2))-msg.tcenter0;
        msg.bttntext1=(msg.x+thm.msgbox_width)-(((thm.msgbox_width-(thm.msgboxbtn_width*2))/4)+(thm.msgboxbtn_width/2)+msg.tcenter1);//(((msg.bx+thm.msgboxbtn_width)+(((thm.msgbox_width-(thm.msgboxbtn_width*2))/4)*2))+(thm.msgboxbtn_width/2))-msg.tcenter1;
        msg.bttntexty=msg.y+msg.by+(8/2);
        //done/////////////////////////////////////////////////////////////////
        if((cursor.x>=msg.x+msg.bx && cursor.x<=msg.x+msg.bx+thm.msgboxbtn_width&&cursor.y>=msg.y+msg.by&&cursor.y<=msg.y+msg.by+thm.msgboxbtn_height)==0)draw(0,0,thm.msgboxbtn_width,thm.msgboxbtn_height,msgbutton0,msg.x+msg.bx,msg.y+msg.by);else draw(0,0,thm.msgboxbtn_width,thm.msgboxbtn_height,msgbutton1,msg.x+msg.bx,msg.y+msg.by);
        if(msg.type==2){if((cursor.x>=(msg.x+thm.msgbox_width)-(msg.bx+thm.msgboxbtn_width)&& cursor.x<=(msg.x+thm.msgbox_width)-msg.bx&&cursor.y>=msg.y+msg.by&&cursor.y<=msg.y+msg.by+thm.msgboxbtn_height)==0)draw(0,0,thm.msgboxbtn_width,thm.msgboxbtn_height,msgbutton0,(msg.x+thm.msgbox_width)-(msg.bx+thm.msgboxbtn_width),msg.y+msg.by);else draw(0,0,thm.msgboxbtn_width,thm.msgboxbtn_height,msgbutton1,(msg.x+thm.msgbox_width)-(msg.bx+thm.msgboxbtn_width),msg.y+msg.by);}
        if( (cursor.y-msg.y)/thm.menu_height==0 && ((cursor.x-msg.x)-EdgeAlign(thm.msgbox_width,thm.menu_width,1))/thm.menu_width==(thm.msgbox_width/thm.menu_width)-1)
        {draw(0,0,thm.menu_width,thm.menu_height,msgexit1,msg.x+(thm.menu_width*((thm.msgbox_width/thm.menu_width)-1))+EdgeAlign(thm.msgbox_width,thm.menu_width,1),msg.y);}
        else
        {draw(0,0,thm.menu_width,thm.menu_height,msgexit0,msg.x+(thm.menu_width*((thm.msgbox_width/thm.menu_width)-1))+EdgeAlign(thm.msgbox_width,thm.menu_width,1),msg.y);}
        print(msg.bttntext0,msg.bttntexty,msg.btext0,rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));
        if(msg.type==2){print(msg.bttntext1,msg.bttntexty,msg.btext1,rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));}
        if(Controller.Buttons & FIRSTCLICK && FIRSTCLICKREADY==1)
        {
                              FIRSTCLICKREADY=0;
                              if(cursor.x>=msg.x&&cursor.x<=msg.x+thm.msgbox_width)
                              {
                              if((cursor.y-msg.y)/thm.menu_height==0){
                              if(((cursor.x-msg.x)-EdgeAlign(thm.msgbox_width,thm.menu_width,1))/thm.menu_width==((thm.msgbox_width/thm.menu_width)-1)){break;}
                              else
                              {msg.carry=1;msg.carryx=cursor.x-msg.x; msg.carryy=cursor.y-msg.y;}
                              }
                              else
                              if(cursor.y>=msg.y+msg.by&&cursor.y<=msg.y+msg.by+thm.msgboxbtn_height)
                              {
                              if(cursor.x>=msg.x+msg.bx && cursor.x<=msg.x+msg.bx+thm.msgboxbtn_width){return(1);}
                              else
                              if(msg.type==2&&cursor.x>=(msg.x+thm.msgbox_width)-(msg.bx+thm.msgboxbtn_width)&& cursor.x<=(msg.x+thm.msgbox_width)-msg.bx){return(2);}
                              }
                              }
        }else{if((Controller.Buttons & FIRSTCLICK)==0)FIRSTCLICKREADY=1;}
        DrawCursor();
        AudStatusRespond();
        flipScreen();
//L & R
        if(Controller.Buttons & PSP_CTRL_LTRIGGER&&(Controller.Buttons & PSP_CTRL_RTRIGGER)==0){if(msg.type==2){cursor.y=msg.y+msg.by+(thm.msgboxbtn_height/2);cursor.x=msg.x+msg.bx+(thm.msgboxbtn_width/2);}}
        else
        if(Controller.Buttons & PSP_CTRL_RTRIGGER&&(Controller.Buttons & PSP_CTRL_LTRIGGER)==0){if(msg.type==2){cursor.y=msg.y+msg.by+(thm.msgboxbtn_height/2);cursor.x=(msg.x+thm.msgbox_width)-(msg.bx+(thm.msgboxbtn_width/2));}}
//Start
if(Controller.Buttons & PSP_CTRL_START && STARTPRESSREADY==1)
{//start
STARTPRESSREADY=0;
if(msg.type==1){halt(15);return(1);}
       else
       if(cursor.y>=msg.y+msg.by&&cursor.y<=msg.y+msg.by+thm.msgboxbtn_height)
                              {
                              if(cursor.x>=msg.x+msg.bx && cursor.x<=msg.x+msg.bx+thm.msgboxbtn_width){return(1);}
                              else
                              if(msg.type==2&&cursor.x>=(msg.x+thm.msgbox_width)-(msg.bx+thm.msgboxbtn_width)&& cursor.x<=(msg.x+thm.msgbox_width)-msg.bx){return(2);}
                              }
}//start
else{if((Controller.Buttons & PSP_CTRL_START)==0)STARTPRESSREADY=1;}
}
FIRSTCLICKREADY=0;
return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////FILE CALLS
////////////////////////////////////FULLSCREEN NOTEPAD
void Notepad_Fullscreen()
{
                         Desktop=0;
ReadTextSheets();
while(1)
{//begin main while
DrawWallpaper();
        draw(0,0,thm.fullscreen_width,thm.fullscreen_height,txtback1,0,0);
        sceCtrlReadBufferPositive(&Controller,1);
if((cursor.x/thm.menu_width==0 && cursor.y/thm.menu_height==0)==0)draw(0,0,thm.menu_width,thm.menu_height,txtsizeswt0,0,0);else draw(0,0,thm.menu_width,thm.menu_height,txtsizeswt1,0,0);//size
if((cursor.x/thm.menu_width==((thm.fullscreen_width/thm.menu_width)-1) && cursor.y/thm.menu_height==0)==0)draw(0,0,thm.menu_width,thm.menu_height,txtexit0,(thm.menu_width*((thm.fullscreen_width/thm.menu_width)-1)),0); else draw(0,0,thm.menu_width,thm.menu_height,txtexit1,(thm.menu_width*((thm.fullscreen_width/thm.menu_width)-1)),0);//exit
if((cursor.x/thm.menu_width==((thm.fullscreen_width/thm.menu_width)-2) && cursor.y/thm.menu_height==1)==0)draw(0,0,thm.menu_width,thm.menu_height,txtbck0,(thm.menu_width*((thm.fullscreen_width/thm.menu_width)-2)),(thm.menu_height*1));else draw(0,0,thm.menu_width,thm.menu_height,txtbck1,(thm.menu_width*((thm.fullscreen_width/thm.menu_width)-2)),(thm.menu_height*1));//back
if((cursor.x/thm.menu_width==((thm.fullscreen_width/thm.menu_width)-1) && cursor.y/thm.menu_height==1)==0)draw(0,0,thm.menu_width,thm.menu_height,txtfwd0,(thm.menu_width*((thm.fullscreen_width/thm.menu_width)-1)),(thm.menu_height*1));else draw(0,0,thm.menu_width,thm.menu_height,txtfwd1,(thm.menu_width*((thm.fullscreen_width/thm.menu_width)-1)),(thm.menu_height*1));//forw
print(1,thm.menu_height+((8*2)-thm.menu_height),"scroll:",rgb(atoi(clr.red[2]),atoi(clr.grn[2]),atoi(clr.blu[2])));
 //8*7 to push over and prevent "scroll:" to txt.scroll[] overlapping!!<--
 char show_scroll[56];
 sprintf(show_scroll,"%i",txt.scroll[txt.active]);
 print(1+(8*7),thm.menu_height+((8*2)-thm.menu_height),show_scroll,rgb(atoi(clr.red[2]),atoi(clr.grn[2]),atoi(clr.blu[2])));
int linerope;
for(linerope=1;linerope<=(thm.fullscreen_height-(thm.menu_height+(8*2)))/(8*2); linerope++)print(1,(16*1)+(16*(linerope)),txt.lines[linerope+(txt.active*(thm.fullscreen_height/(8*2)))],rgb(atoi(clr.red[0]),atoi(clr.grn[0]),atoi(clr.blu[0])));
if(Controller.Buttons & FIRSTCLICK && FIRSTCLICKREADY==1)
{//CLICK
FIRSTCLICKREADY=0;
if(cursor.y/thm.menu_height==0)
{//menu 1
if(cursor.x/thm.menu_width==0){txt.fullscreen[txt.active]=0;ReadTextSheets();Desktop=1;break;}
else
if(cursor.x/thm.menu_width==((thm.fullscreen_width/thm.menu_width)-1))
{
txt.show[txt.active]=0;
txt.scroll[txt.active]=0;
for(counter=1; counter<=(thm.fullscreen_height-(thm.menu_height+(8*2)))/(8*2); counter++)txt.lines[(txt.active*17)+counter][0]='\0';
//ORDER FIXING SCRIPT
Repair_Depth(txt.depth[txt.active]);txt.depth[txt.active]=-1;txt.ProgramsRunningC--;ProgramsRunningC--;Desktop=1;
break;
}
}//menu 1
else
if(cursor.y/thm.menu_height==1)
{//menu 2
if(cursor.x/thm.menu_width==((thm.fullscreen_width/thm.menu_width)-1)){txt.scroll[txt.active]++;ReadTextSheets();}//<--forward
else//use else to try to cut loading time for checking *back* if not needed
if(cursor.x/thm.menu_width==((thm.fullscreen_width/thm.menu_width)-2)){if(txt.scroll[txt.active]>0){txt.scroll[txt.active]--;ReadTextSheets();}}//back<--
}//menu 2
}//CLICK
else{if((Controller.Buttons & FIRSTCLICK)==0)FIRSTCLICKREADY=1;}
//SPEED SCROLL
if(Controller.Buttons & PSP_CTRL_LTRIGGER&&(Controller.Buttons & PSP_CTRL_RTRIGGER)==0){if(txt.scroll[txt.active]>0){txt.scroll[txt.active]--;ReadTextSheets();}}
else
if(Controller.Buttons & PSP_CTRL_RTRIGGER&&(Controller.Buttons & PSP_CTRL_LTRIGGER)==0){txt.scroll[txt.active]++;ReadTextSheets();}
AudStatusRespond();
DrawCursor();
flipScreen();
}//end main while
}//end fullscreen function

////////////////////////////////////FULLSCREEN NOTEPAD
///////////////////////////////////////////////////1.5 eboot loader THIS DOESN'T WORK ON VRS1.00 PSP'S<--
int Call_PBP(char *PBPFile)
{
scePowerSetClockFrequency(222,222,111);MP3_End();
  struct SceKernelLoadExecParam EBOOTPBP;
  const u32 Total_Length = strlen(PBPFile)+1;	// The Entire Length of the FileDirectory+FileName & +1
  EBOOTPBP.args = Total_Length;
  EBOOTPBP.argp = (const char*)PBPFile;//change char into char*
  EBOOTPBP.key = NULL;//Null no key is initiated
  EBOOTPBP.size = sizeof(EBOOTPBP)+Total_Length;
  if(sceKernelLoadExec(File,&EBOOTPBP)<0){ConvertProcessorPower();InitMessage("System","*PBP Launch Failed.","OK","",1);DisplayMsgbox();return 0;}// Load & check success: 0 == Failure
  return 1;//init messge on failure, but can't now cause Display Message is not called before this//NOW WE CAN BECAUSE THAT ISSUE HAS BEEN TAKEN CARE OF...
}
///////////////////////////////////////////////////1.5 eboot loader THIS DOESN'T WORK ON VRS1.00 PSP'S<--
///////////////////////////////////////////////////////////////////////////////////////////////FILE CALLS
///////////////////////////////////////////////////////////UMD PROCEDURE
int ExecuteUmd()
{
/* // Wait for disc and mount to filesystem
 char Game[35];//really need 31, but +4 just incase ;)
 sprintf(Game,"%s","disc0:/psp_game/sysdir/boot.bin");
 if(sceUmdCheckMedium(0) == 0)
 {
    sceUmdWaitDriveStat(UMD_WAITFORDISC);
 }sceUmdActivate(1, "disc0:");
scePowerSetClockFrequency(222,222,111);MP3_End();
  struct SceKernelLoadExecParam EBOOTPBP;
  const u32 Total_Length = strlen(Game)+1;	// The Entire Length of the FileDirectory+FileName & +1
  EBOOTPBP.args = Total_Length;
  EBOOTPBP.argp = (const char*)Game;//change char into char*
  EBOOTPBP.key = NULL;//Null no key is initiated
  EBOOTPBP.size = sizeof(EBOOTPBP)+Total_Length;
 // play the game... need to advance this for video disks too still :'(
 // Now you can access the UMD using standard sceIo functions
 if((sceKernelLoadExec(Game,&EBOOTPBP))<0){ConvertProcessorPower();InitMessage("System","*UMD Launch Failed.","OK","",1);DisplayMsgbox();return 0;}
*/return(1);
}
///////////////////////////////////////////////////////////UMD PROCEDURE
//////////////////////Loading a PRX
int LoadAndStartModule_PRX(char *ModuleFILE, int UserMode)//UserMode mode: 1==true; 0 == false;
{//start moduling
//**ERROR INSTALL HANDLERS**\//
//pspDebugInstallKprintfHandler(NULL);
//pspDebugInstallErrorHandler(NULL);
//pspDebugInstallStdoutHandler(pspDebugScreenPrintData);
//pspSdkInstallNoPlainModuleCheckPatch();//uses : #include <pspsdk.h>
SceKernelLMOption moduleprx;
                  moduleprx.mpidtext = (UserMode+1);// 2 is equivalent to usermode ;)
                  moduleprx.mpiddata = (UserMode+1);// 2 is equivalent to usermode ;)
                  moduleprx.position = 0;
                  moduleprx.access = 1;
                  moduleprx.size = sizeof(moduleprx);
SceUID PrxID=0;
PrxID = sceKernelLoadModule(ModuleFILE,0,UserMode > 0 ? &moduleprx : NULL);// If in usermode, don't call as NULL >:// this carrys MS for Memory Stick ;)
int prxstatus=-1;
if( ( sceKernelStartModule (PrxID, 0,NULL,&prxstatus,NULL) ) !=0)// it was :if( ( sceKernelStartModule (PrxID, 0,NULL,&prxstatus,moduleprx) ) !=0)
{//I think this is an okay error check<-
    //do nothing until necessary... :), but this is on an errors existance
}//last argument is 0 for usermode! #3 is NULL becaus it's okay, and I don't know wtf it's it's honestly asking for... :'(
//Finish MODULING: Stop & Unload Relative MODULE
sceKernelStopModule(PrxID, 0, NULL,&prxstatus,NULL);// it was:sceKernelStopModule(PrxID, 0, NULL,&prxstatus,moduleprx);
sceKernelUnloadModule(PrxID);
return prxstatus;
}//end moduling
//////////////////////Loading a PRX
void ActivateFile()
{
     char*FileExtention;
     FileExtention=strrchr(FileAdd,'.');
sprintf(File,"%s%s",FileHold,FileAdd);
ProgramsRunningC++;//prevents the use of zero... gets fixed if no file is activated here->//-1 == nothing running 0= 1 1=2 etc...
/////////////
while(1)
{//while
if(FileExtention!=NULL)
{//visible extensions
if(stricmp(FileExtention,".mp3")==0)//*.mp3
{
if(aud.isplaying==1)if(aud.type==0)MP3_End();//else if(aud.type==1)OGG_End();
sprintf(aud.currently_playingpth,"%s",File);
sprintf(aud.currently_playing,"%s",FileAdd);
aud.show=1;aud.type=0;Call_Music();break;}
else
/*if(stricmp(FileExtention,".ogg")==0)//*.ogg
{
//if(aud.isplaying==1)if(aud.type==0)MP3_End();//else if(aud.type==1)OGG_End();
sprintf(aud.currently_playingpth,"%s",File);
sprintf(aud.currently_playing,"%s",FileAdd);
aud.show=1;aud.type=1;Call_Music();break;}
else*/
if((stricmp(FileExtention,".pbp")==0))//*.pbp
{Call_PBP(File);break;}
else
if((stricmp(FileExtention,".txt")==0||stricmp(FileExtention,".log")==0||
stricmp(FileExtention,".rtf")==0||stricmp(FileExtention,".vbs")==0||
stricmp(FileExtention,".c")==0||stricmp(FileExtention,".c++")==0||stricmp(FileExtention,".ini")==0)&&txt.ProgramsRunningC<4)//*.txt//<5 cause FIVE IS AS HIGH AS IT CAN GOOOOOOO!!! //*.txt
{txt.ProgramsRunningC++;txt.active=Find_Open_Notepad();Prepare_Depth(d.depth,1);txt.depth[txt.active]=0;sprintf(txt.file[txt.active],"%s",File);if(txt.fullscreen[txt.active]!=1){ReadTextSheets();}else{Notepad_Fullscreen();}txt.show[txt.active]=1;break;}
else if((txt.ProgramsRunningC<4)==0){ProgramsRunningC--;break;}
}//visible extensions
ProgramsRunningC--;
InitMessage("System","File type unknown.","OK","",1);
DisplayMsgbox();
break;
}//while
}//stop activation of files

//////////////////////////////
/////////////////////////////////////////////////////FULLSCREEN DIRECTORIES<--
void Browse_Fullscreen()
{
Desktop=0;
     fld.fullscreen[fld.active]=1;
Browse(fld.dir[fld.active]);
while(1)
{//while
sceCtrlReadBufferPositive(&Controller,1);
////////////////////////////////
//DRAW
DrawWallpaper();
             draw(0,0,thm.fullscreen_width,thm.fullscreen_height,fldback1,0,0);
             if((cursor.x/thm.menu_width==0 && cursor.y/thm.menu_height==0)==0)draw(0,0,thm.menu_width,thm.menu_height,fldsizeswt0,0,0);else draw(0,0,thm.menu_width,thm.menu_height,fldsizeswt1,0,0);
             if((cursor.y/thm.menu_height==0 && cursor.x/thm.menu_width==((thm.fullscreen_width/thm.menu_width)-1))==0){draw(0,0,thm.menu_width,thm.menu_height,fldexit0,thm.menu_width*((thm.fullscreen_width/thm.menu_width)-1),0);}else {draw(0,0,thm.menu_width,thm.menu_height,fldexit1,thm.menu_width*((thm.fullscreen_width/thm.menu_width)-1),0);}
             print(thm.menu_width,(8/2),fld2.dis_dir[fld.active],rgb(atoi(clr.red[3]),atoi(clr.grn[3]),atoi(clr.blu[3])));
////////////////////////////////
 for(fld.column=0; fld.column<thm.fullscreen_width/(ico.x+ico.splitx); fld.column++)
     {//horizontal loop
 for(fld.counter=0; fld.counter<=3; fld.counter++)
 {//vertical loop
 if(fld.file[(fld.active*33)+(fld.counter+(4*fld.column))][0]!='\0')
 {//1
 if(((cursor.x-(ico.spacex+(ico.spacex*fld.column)))/ico.x==fld.column && ((cursor.y-17)-(ico.spacey+(ico.spacey*fld.counter)))/ico.y==fld.counter && cursor.x>=ico.spacex && cursor.y>=(17+ico.spacey))==0)
 {//2
//////////////

 switch(fld.format[(fld.active*33)+(fld.counter+(fld.column*4))])
         {
          case 1:draw(0,0,48,48,folder0,(ico.x*fld.column)+(ico.spacex*(fld.column+1)),((ico.y*fld.counter)+thm.menu_height)+(ico.spacey*(fld.counter+1)));break;
          case 2:draw(0,0,48,48,Faud0,(ico.x*fld.column)+(ico.spacex*(fld.column+1)),((ico.y*fld.counter)+thm.menu_height)+(ico.spacey*(fld.counter+1)));break;
          case 3:draw(0,0,48,48,Fpic0,(ico.x*fld.column)+(ico.spacex*(fld.column+1)),((ico.y*fld.counter)+thm.menu_height)+(ico.spacey*(fld.counter+1)));break;
          case 4:draw(0,0,48,48,Ftxt0,(ico.x*fld.column)+(ico.spacex*(fld.column+1)),((ico.y*fld.counter)+thm.menu_height)+(ico.spacey*(fld.counter+1)));break;
          case 5:draw(0,0,48,48,Fpbp0,(ico.x*fld.column)+(ico.spacex*(fld.column+1)),((ico.y*fld.counter)+thm.menu_height)+(ico.spacey*(fld.counter+1)));break;
               default:draw(0,0,48,48,Funk0,(ico.x*fld.column)+(ico.spacex*(fld.column+1)),((ico.y*fld.counter)+16)+(ico.spacey*(fld.counter+1)));
         } 
//////////////                                                                     

 }//2
 else
 {//2
 //////////////

 switch(fld.format[(fld.active*33)+(fld.counter+(fld.column*4))])
         {
          case 1:draw(0,0,48,48,folder1,(ico.x*fld.column)+(ico.spacex*(fld.column+1)),((ico.y*fld.counter)+thm.menu_height)+(ico.spacey*(fld.counter+1)));break;
          case 2:draw(0,0,48,48,Faud1,(ico.x*fld.column)+(ico.spacex*(fld.column+1)),((ico.y*fld.counter)+thm.menu_height)+(ico.spacey*(fld.counter+1)));break;
          case 3:draw(0,0,48,48,Fpic1,(ico.x*fld.column)+(ico.spacex*(fld.column+1)),((ico.y*fld.counter)+thm.menu_height)+(ico.spacey*(fld.counter+1)));break;
          case 4:draw(0,0,48,48,Ftxt1,(ico.x*fld.column)+(ico.spacex*(fld.column+1)),((ico.y*fld.counter)+thm.menu_height)+(ico.spacey*(fld.counter+1)));break;
          case 5:draw(0,0,48,48,Fpbp1,(ico.x*fld.column)+(ico.spacex*(fld.column+1)),((ico.y*fld.counter)+thm.menu_height)+(ico.spacey*(fld.counter+1)));break;
               default:draw(0,0,48,48,Funk1,(ico.x*fld.column)+(ico.spacex*(fld.column+1)),((ico.y*fld.counter)+16)+(ico.spacey*(fld.counter+1)));
         } 
//////////////   
 }//2
 print((ico.x*fld.column)+(ico.spacex*(fld.column+1)),(((ico.y*fld.counter)+17)+(ico.spacey*(fld.counter+1)))+(ico.y-8),fld2.dis_file[(fld.active*33)+(fld.counter+(fld.column*4))],rgb(atoi(clr.red[4]),atoi(clr.grn[4]),atoi(clr.blu[4])));
 }//1
 }//vertical loop
 }//horizontal loop
 ///////////////////////////////add
//BUTTON INPPUT...
BREAK1:
if(Controller.Buttons & FIRSTCLICK && FIRSTCLICKREADY==1)
     {
                           FIRSTCLICKREADY=0;
if(cursor.y/thm.menu_height==0 && cursor.x/thm.menu_width==0){fld.fullscreen[fld.active]=0;fld.page_should_be[fld.active]=fld.current_page[fld.active]*2;Browse(fld.dir[fld.active]);Desktop=1;break;}
else
if(cursor.y/thm.menu_height==0 && cursor.x/thm.menu_width==((thm.fullscreen_width/thm.menu_width)-1)){fld.show[fld.active]=0;Repair_Depth(fld.depth[fld.active]);fld.depth[fld.active]=-1;fld.ProgramsRunningC--;ProgramsRunningC--;Desktop=1;break;}
else
{//not exit

                           fld.column=0;
while(fld.column<thm.fullscreen_width/(ico.x+ico.splitx))
{
fld.counter=0;
while(fld.counter<=3)
{
if((cursor.x-(ico.spacex+(ico.spacex*fld.column)))/ico.x==fld.column && ((cursor.y-thm.menu_height)-(ico.spacey+(ico.spacey*fld.counter)))/ico.y==fld.counter && cursor.x>=ico.spacex && cursor.y>=(thm.menu_height+ico.spacey))
{
if(fld.file[(fld.active*33)+(fld.counter+(fld.column*4))][0]!='\0')
{//is not blank area
/////////type
if(fld.type[(fld.active*33)+(fld.counter+(fld.column*4))]!=0)
{
sprintf(FileHold,"%s",fld.dir[fld.active]);
sprintf(FileAdd,"%s",fld.file[(fld.active*33)+(fld.counter+(fld.column*4))]);
ActivateFile();goto BREAK1;
}
else
{
    sprintf(DirectoryAdd,"%s",fld.dir[fld.active]);
    sprintf(fld.dir[fld.active],"%s%s/",DirectoryAdd,fld.file[(fld.active*33)+(fld.counter+(fld.column*4))]);
    DirectoryAdd[0]='\0';Browse(fld.dir[fld.active]);goto BREAK1;
}
/////////type
}//is not blank area
}
fld.counter++;
}
fld.column++;
}
}//not exit
     }else{if((Controller.Buttons & FIRSTCLICK)==0)FIRSTCLICKREADY=1;}
//L & R
if(Controller.Buttons & PSP_CTRL_LTRIGGER&&(Controller.Buttons & PSP_CTRL_RTRIGGER)==0)
{
if(fld.current_page[fld.active]>0)
{fld.page_should_be[fld.active]=fld.current_page[fld.active]-1;}
else
{fld.dir[fld.active][GoBack(fld.dir[fld.active])]='\0';}
Browse(fld.dir[fld.active]);halt(15);
}
else
if(Controller.Buttons & PSP_CTRL_RTRIGGER&&(Controller.Buttons & PSP_CTRL_LTRIGGER)==0)
{
if(fld.more_pages_exists[fld.active]==1)fld.page_should_be[fld.active]=fld.current_page[fld.active]+1;
Browse(fld.dir[fld.active]);halt(15);
}
///////////////////////////////add
AudStatusRespond();
DrawCursor();
flipScreen();
}//while
}//end function
/////////////////////////////////////////////////////FULLSCREEN DIRECTORIES<--

//AUDIO BUTTONS
void Audio_ButtnChk()
{//Audio position checking

//this way if it activates unlike in the if no x it shouldn't be much skipping :)
if(lround((cursor.y-aud.y)/thm.menu_height)==0)
{
if( ((cursor.x-aud.x)/thm.menu_width)==0){aud.size=aud.size*-1;}//size
else
if( ((cursor.x-aud.x)-EdgeAlign(thm.mtopbar_width,thm.menu_width,1))/thm.menu_width==(thm.mtopbar_width/thm.menu_width)-1){aud.show=0;}//exit
else{aud.carryx=cursor.x-aud.x;aud.carryy=cursor.y-aud.y;aud.carry=1;}
}
else
if(((cursor.y-aud.y)-((((thm.mtopbar_height/thm.mbutton_height)-1)*thm.mbutton_height)-EdgeAlign(thm.mtopbar_height,thm.mbutton_height,2)))/thm.mbutton_height==0)//+17 cause pics on second row were 16+1 ;)//NOT ANYMORE...
{//second row

//if(((cursor.x-aud.x)/thm.mbutton_width)==0){}//reverse
//if(((cursor.x-aud.x)/thm.mbutton_width)==1){}//fast forward
if(((cursor.x-aud.x)/thm.mbutton_width)==2){if(aud.isplaying==-2)Call_Music();else if(aud.isplaying==0){if(aud.type==0)MP3_Play();else /*if(aud.type==1)OGG_Play();*/aud.isplaying=1;}else{if(aud.type==0)MP3_Pause();/*else if(aud.type==1)OGG_Play();*/aud.isplaying=!aud.isplaying;}}//play & pause
if(((cursor.x-aud.x)/thm.mbutton_width)==3){if(aud.isplaying==1){if(aud.type==0)MP3_Stop();/*else if(aud.type==1)OGG_Stop();*/sprintf(aud.last,"%s",aud.currently_playing);aud.isplaying=-2;}}//stop
//if(((cursor.x-aud.x)/thm.mbutton_width)==4){}//may be used later
//if(((cursor.x-aud.x)/thm.mbutton_width)==5){}//may be used later
if(( ((cursor.x-aud.x)-EdgeAlign(thm.mtopbar_width,thm.mbutton_width,1))/thm.mbutton_width)==((thm.mtopbar_width/thm.mbutton_width)-4)){if(aud.style==1){aud.style=0;} else{aud.style=1;}}
if(( ((cursor.x-aud.x)-EdgeAlign(thm.mtopbar_width,thm.mbutton_width,1))/thm.mbutton_width)==((thm.mtopbar_width/thm.mbutton_width)-3)){if(aud.style==2){aud.style=0;} else{aud.style=2;}}
if(( ((cursor.x-aud.x)-EdgeAlign(thm.mtopbar_width,thm.mbutton_width,1))/thm.mbutton_width)==((thm.mtopbar_width/thm.mbutton_width)-2)){if(aud.style==3){aud.style=0;} else{aud.style=3;}}
//if(((cursor.x-aud.x)/thm.mbutton_width)==((thm.mtopbar_width/thm.menu_width)-1))){}//may be used later
}//second row
}//end audio position checking
/////////////////////////////////////////////////////
void Notepad_ButtnChk()
{//begin function
if((cursor.y-txt.y[txt.active])/thm.menu_height==0)
{//y coordinates == Bar
if((cursor.x-txt.x[txt.active])/thm.menu_width==0){txt.fullscreen[txt.active]=1;Notepad_Fullscreen();}//size
else
if( ((cursor.x-txt.x[txt.active])-EdgeAlign(thm.twindow_width,thm.menu_width,1))/thm.menu_width==(thm.twindow_width/thm.menu_width)-1)
{
txt.show[txt.active]=0;
txt.scroll[txt.active]=0;
for(txt.counter=1; txt.counter<=(thm.fullscreen_height-(thm.menu_height+(8*2)))/(8*2); txt.counter++)txt.lines[(txt.active*(thm.fullscreen_height/(8*2)))+txt.counter][0]='\0';
Repair_Depth(txt.depth[txt.active]);txt.depth[txt.active]=-1;txt.ProgramsRunningC--;ProgramsRunningC--;
}
else{txt.carryx=cursor.x-txt.x[txt.active];txt.carryy=cursor.y-txt.y[txt.active];txt.carry[txt.active]=1;}
}//y coordinates == Bar
else
if((cursor.y-txt.y[txt.active])/thm.menu_height==1)
{//user is attempting secondary menu usage~~
if((cursor.x-txt.x[txt.active])/thm.menu_width==((thm.twindow_width/thm.menu_width)-1)){txt.scroll[txt.active]++;ReadTextSheets();}//<--forward
else//use else to try to cut loading time for checking *back* if not needed
if((cursor.x-txt.x[txt.active])/thm.menu_width==((thm.twindow_width/thm.menu_width)-2)){if(txt.scroll[txt.active]>0){txt.scroll[txt.active]--;ReadTextSheets();}}//back<--
}//user is attempting secondary menu usage~~
}//end function
/////////////////////////////////////////////////////
void Folder_ButtnChk()
{
     if((cursor.y-fld.y[fld.active])/thm.menu_height==0)
     {
     if( ((cursor.x-fld.x[fld.active])-EdgeAlign(thm.folder_width,thm.menu_width,1)) /thm.menu_width==(thm.folder_width/thm.menu_width)-1){fld.show[fld.active]=0;Repair_Depth(fld.depth[fld.active]);fld.depth[fld.active]=-1;fld.ProgramsRunningC--;ProgramsRunningC--;}//exit
     else
     if((cursor.x-fld.x[fld.active])/thm.menu_width==0){fld.page_should_be[fld.active]=fld.current_page[fld.active]/2;Browse_Fullscreen();}//size
     else{fld.carryx=cursor.x-fld.x[fld.active];fld.carryy=cursor.y-fld.y[fld.active];fld.carry[fld.active]=1;}
     }
     else
     if((cursor.y-fld.y[fld.active])/thm.menu_height==1)
     {
     if((cursor.x-fld.x[fld.active])/thm.menu_width==(304/thm.menu_width)-1){if(fld.more_pages_exists[fld.active]==1){fld.page_should_be[fld.active]=fld.current_page[fld.active]+1;Browse(fld.dir[fld.active]);}}//forward-->
     if((cursor.x-fld.x[fld.active])/thm.menu_width==(304/thm.menu_width)-2){if(fld.current_page[fld.active]>0){fld.page_should_be[fld.active]=fld.current_page[fld.active]-1;}else{fld.dir[fld.active][GoBack(fld.dir[fld.active])]='\0';}Browse(fld.dir[fld.active]);}//back<--
     }
     else
     {//1
         if(cursor.x>=fld.x[fld.active]&&cursor.x<=fld.x[fld.active]+304)//prevents the borders from being active upon clicking on them...//not anymore!!
         {
         if(cursor.y<=fld.y[fld.active]+176)
         {
         //READ CONTROLLER INPUT...
//(((cursor.x-fld.x[fld.active])/(ico.x+ico.smallspacex))*ico.x)/ico.
if((/*2*/(/*1*/(cursor.x-((ico.smallspacex*(((cursor.x-fld.x[fld.active])/(ico.x+ico.smallspacex))+1))+fld.x[fld.active]))/ico.x/*1*/) * (((176-(thm.menu_height*2))/(ico.y+ico.smallspacey))+0)/*2*/)   +  (/*3*/(cursor.y-((thm.menu_height*2)+fld.y[fld.active]))/(ico.y+ico.smallspacey)/*3*/)/*Lock*/</*Lock*/(thm.folder_width/ico.x)*((thm.folder_height-(thm.menu_height*2))/ico.y)  )
{///file
if(fld.type[(/*2*/(/*1*/(cursor.x-((ico.smallspacex*(((cursor.x-fld.x[fld.active])/(ico.x+ico.smallspacex))+1))+fld.x[fld.active]))/ico.x/*1*/) * (((176-(thm.menu_height*2))/(ico.y+ico.smallspacey))+0)/*2*/)   +  (/*3*/(cursor.y-((thm.menu_height*2)+fld.y[fld.active]))/(ico.y+ico.smallspacey)/*3*/)]!=0)
{///type
if(fld.file[(/*2*/(/*1*/(cursor.x-((ico.smallspacex*(((cursor.x-fld.x[fld.active])/(ico.x+ico.smallspacex))+1))+fld.x[fld.active]))/ico.x/*1*/) * (((176-(thm.menu_height*2))/(ico.y+ico.smallspacey))+0)/*2*/)   +  (/*3*/(cursor.y-((thm.menu_height*2)+fld.y[fld.active]))/(ico.y+ico.smallspacey)/*3*/)][0]!='\0')
{////////3
sprintf(FileHold,"%s",fld.dir[fld.active]);
sprintf(FileAdd,"%s",fld.file[(/*2*/(/*1*/(cursor.x-((ico.smallspacex*(((cursor.x-fld.x[fld.active])/(ico.x+ico.smallspacex))+1))+fld.x[fld.active]))/ico.x/*1*/) * (((176-(thm.menu_height*2))/(ico.y+ico.smallspacey))+0)/*2*/)   +  (/*3*/(cursor.y-((thm.menu_height*2)+fld.y[fld.active]))/(ico.y+ico.smallspacey)/*3*/)]);
ActivateFile();
}///////3
}///type
else
{///type
    sprintf(DirectoryAdd,"%s",fld.dir[fld.active]);
    sprintf(fld.dir[fld.active],"%s%s/",DirectoryAdd,fld.file
    [(/*2*/(/*1*/(cursor.x-((ico.smallspacex*(((cursor.x-fld.x[fld.active])/(ico.x+ico.smallspacex))+1))+fld.x[fld.active]))/ico.x/*1*/) * (((176-(thm.menu_height*2))/(ico.y+ico.smallspacey))+0)/*2*/)   +  (/*3*/(cursor.y-((thm.menu_height*2)+fld.y[fld.active]))/(ico.y+ico.smallspacey)/*3*/)]);
    DirectoryAdd[0]='\0';fld.current_page[fld.active]=0;Browse(fld.dir[fld.active]);
}///type
}///file
//         ActivateFile();
         }
         }
     }//1
}
/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////SYSTEM HALL
void SettingsHallSystem()
{
     Desktop=0;
while(1)
{
        sceCtrlReadBufferPositive(&Controller,1);
        DrawWallpaper();draw(0,0,thm.fullscreen_width,thm.fullscreen_height,mainscreen,0,0);int sxotze=0;
        int ssssyyyyyy=lround(16*(cursor.y/16));
        char sttmosuespeed[4];sprintf(sttmosuespeed,"%f",cursor.speed);
        draw(0,0,thm.fullscreen_width,16,sttselection,0,ssssyyyyyy);
        //changes are as so setts[20][0]; and setts[sxotze][0]=changes;
        //only 16 may exist:thm.fullscreen_height/16=17 1 at top for area title and bottom for explanation :) if you do 17 though, it will be off screen cause it would be(0to17)=18
        //****sxotze=0***\//
        print(0,(3)+16*sxotze,"  Settings             (applied immediately)",rgb(atoi(clr.red[3]),atoi(clr.grn[3]),atoi(clr.blu[3])));//0
        print(thm.fullscreen_width-(8*8),(3)+16*sxotze,(ControllerRegion==-1?"O Cancel":"X Cancel"),rgb(atoi(clr.red[6]),atoi(clr.grn[6]),atoi(clr.blu[6])));//0
        //****sxotze=0***\//
        sxotze++;
        //****sxotze+=***\//
        print(0,(3)+16*sxotze,"Stop XMB PowerSave upon idle",rgb(atoi(clr.red[0]),atoi(clr.grn[0]),atoi(clr.blu[0])));if(StopPowerSave==1)print(thm.fullscreen_width-(8*3),(3)+16*sxotze,"Yes",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));else print(thm.fullscreen_width-(8*2),(3)+16*sxotze,"No",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));sxotze++;//1
        print(0,(3)+16*sxotze,"Attempt *Standby on hold key",rgb(atoi(clr.red[0]),atoi(clr.grn[0]),atoi(clr.blu[0])));if(Standby==1)print(thm.fullscreen_width-(8*3),(3)+16*sxotze,"Yes",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));else print(thm.fullscreen_width-(8*2),(3)+16*sxotze,"No",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));sxotze++;//2
        print(0,(3)+16*sxotze,"Affect lag behavior (repair)",rgb(atoi(clr.red[0]),atoi(clr.grn[0]),atoi(clr.blu[0])));if(RepairLag==1)print(thm.fullscreen_width-(8*3),(3)+16*sxotze,"Yes",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));else print(thm.fullscreen_width-(8*2),(3)+16*sxotze,"No",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));sxotze++;//3
        print(0,(3)+16*sxotze,"Select system mouse speed1-6",rgb(atoi(clr.red[0]),atoi(clr.grn[0]),atoi(clr.blu[0])));print(thm.fullscreen_width-8,(3)+16*sxotze,sttmosuespeed,rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));sxotze++;//4
        print(0,(3)+16*sxotze,"Display UserName (*Desktop*)-x-",rgb(atoi(clr.red[0]),atoi(clr.grn[0]),atoi(clr.blu[0])));print(thm.fullscreen_width-8,(3)+16*sxotze,"",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));sxotze++;//5
        print(0,(3)+16*sxotze,"Switch between pointer modes",rgb(atoi(clr.red[0]),atoi(clr.grn[0]),atoi(clr.blu[0])));if(KrnlMode==1)print(thm.fullscreen_width-(8*6),(3)+16*sxotze,"Analog",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));else print(thm.fullscreen_width-(8*5),(3)+16*sxotze,"D-Pad",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));sxotze++;//6
        print(0,(3)+16*sxotze,"Alternate system button mode",rgb(atoi(clr.red[0]),atoi(clr.grn[0]),atoi(clr.blu[0])));if(ControllerRegion==-1){print(thm.fullscreen_width-(8*2),(3)+16*sxotze,"UK",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));}else{print(thm.fullscreen_width-(8*2),(3)+16*sxotze,"JP",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));}sxotze++;//this is from -1 to 1 but to show it to user use the integer +4/4 so it looks like 0 to 1 cause 1+4=5 /4 =1 and -1 +4 =3 / 4 = 0 when rounded :)
        print(0,(3)+16*sxotze,"Select *sys. processor level",rgb(atoi(clr.red[0]),atoi(clr.grn[0]),atoi(clr.blu[0])));if(sttpower==-1)print(thm.fullscreen_width-(8*3),(3)+16*sxotze,"low",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));else print(thm.fullscreen_width-(8*4),(3)+16*sxotze,"high",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));sxotze++;//8
        print(0,(3)+16*sxotze,"Remove *fastlink9 extentions",rgb(atoi(clr.red[0]),atoi(clr.grn[0]),atoi(clr.blu[0])));if(ClipFLnk9Ext!=1)print(thm.fullscreen_width-(8*2),(3)+16*sxotze,"No",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));else print(thm.fullscreen_width-(8*3),(3)+16*sxotze,"Yes",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));sxotze++;//9
        print(0,(3)+16*sxotze,"Remove all script extentions",rgb(atoi(clr.red[0]),atoi(clr.grn[0]),atoi(clr.blu[0])));if(ClipCodesExt!=1)print(thm.fullscreen_width-(8*2),(3)+16*sxotze,"No",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));else print(thm.fullscreen_width-(8*3),(3)+16*sxotze,"Yes",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));sxotze++;//10
        print(0,(3)+16*sxotze,"Remove *.MP3 media extention",rgb(atoi(clr.red[0]),atoi(clr.grn[0]),atoi(clr.blu[0])));if(ClipMusicExt!=1)print(thm.fullscreen_width-(8*2),(3)+16*sxotze,"No",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));else print(thm.fullscreen_width-(8*3),(3)+16*sxotze,"Yes",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));sxotze++;//11
        print(0,(3)+16*sxotze,"Remove *.picture* extentions",rgb(atoi(clr.red[0]),atoi(clr.grn[0]),atoi(clr.blu[0])));if(ClipImageExt!=1)print(thm.fullscreen_width-(8*2),(3)+16*sxotze,"No",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));else print(thm.fullscreen_width-(8*3),(3)+16*sxotze,"Yes",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));sxotze++;//12
        print(0,(3)+16*sxotze,"Remove every *text extention",rgb(atoi(clr.red[0]),atoi(clr.grn[0]),atoi(clr.blu[0])));if(ClipPaperExt!=1)print(thm.fullscreen_width-(8*2),(3)+16*sxotze,"No",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));else print(thm.fullscreen_width-(8*3),(3)+16*sxotze,"Yes",rgb(atoi(clr.red[7]),atoi(clr.grn[7]),atoi(clr.blu[7])));sxotze++;//13
        print(0,(3)+16*15,"HKeys Desktop:Strt;Slct; Msgbox:L;R;Strt; Txt:L;R; Fld:L;R;",rgb(atoi(clr.red[0]),atoi(clr.grn[0]),atoi(clr.blu[0])));//14
        print(0,(3)+16*16," *Some options listed are not 100% effective in all cases.*",rgb(atoi(clr.red[6]),atoi(clr.grn[6]),atoi(clr.blu[6])));//15
        //if((cursor.y/thm.menu_height==0 && (cursor.x-EdgeAlign(thm.fullscreen_width,thm.menu_width,1))/thm.menu_width==(thm.fullscreen_width/thm.menu_width)-1)==0){draw(0,0,thm.menu_width,thm.menu_height,sttexit0,(thm.menu_width*((thm.fullscreen_width/thm.menu_width)-1))+EdgeAlign(thm.fullscreen_width,thm.menu_width,1),0);}else {draw(0,0,thm.menu_width,thm.menu_height,sttexit1,(thm.menu_width*((thm.fullscreen_width/thm.menu_width)-1))+EdgeAlign(thm.fullscreen_width,thm.menu_width,1),0);}//exit button
        DrawCursor();
        flipScreen();
        //SECOND CLICK!!
        if(Controller.Buttons & SECONDCLICK && SECONDCLICKREADY==1){Desktop=1;break;}
        else
        {if((Controller.Buttons & SECONDCLICK)==0)SECONDCLICKREADY=1;}
        //FIRST CLICK!!
        if(Controller.Buttons & FIRSTCLICK && FIRSTCLICKREADY==1)
        {
                              FIRSTCLICKREADY=0;
        //if(cursor.y/16==0 && (cursor.x-EdgeAlign(thm.fullscreen_width,thm.menu_width,1))/thm.menu_width==((thm.fullscreen_width/thm.menu_width)-1)){Desktop=1;break;}
        if(cursor.y/16==1){StopPowerSave=StopPowerSave*-1;}
        if(cursor.y/16==2){Standby=Standby*-1;}
        if(cursor.y/16==3){RepairLag=RepairLag*-1;}
        if(cursor.y/16==4){cursor.speed++;if(cursor.speed>6)cursor.speed=1;}
        if(cursor.y/16==5){}
        if(cursor.y/16==6){KrnlMode=KrnlMode*-1;FixControllerMode();}
        if(cursor.y/16==7){ControllerRegion=ControllerRegion*-1;FixControllerMode();SECONDCLICKREADY=0;}
        if(cursor.y/16==8){sttpower=sttpower*-1;ConvertProcessorPower();}
        if(cursor.y/16==9){ClipFLnk9Ext=ClipFLnk9Ext*-1;}
        if(cursor.y/16==10){ClipCodesExt=ClipCodesExt*-1;}
        if(cursor.y/16==11){ClipMusicExt=ClipMusicExt*-1;}
        if(cursor.y/16==12){ClipImageExt=ClipImageExt*-1;}
        if(cursor.y/16==13){ClipPaperExt=ClipPaperExt*-1;}
        if(cursor.y/16==14){}
        if(cursor.y/16==15){}
        //*blah blah blah
        }else{if((Controller.Buttons & FIRSTCLICK)==0)FIRSTCLICKREADY=1;}
        sxotze=0;
        AudStatusRespond();
}FIRSTCLICKREADY=0;
}//system hall end
///////////////////////////////////////////////////////////////////////////////////SYSTEM HALL
////////////////////////////////////////////////////
int ThemesSchemeHall()
{
     while(1)
     {
             sceCtrlReadBufferPositive(&Controller,1);
     DrawWallpaper();draw(0,0,thm.fullscreen_width,thm.fullscreen_height,mainscreen,0,0);                                    sd.column=0;
     for(sd.column=0; sd.column<thm.fullscreen_width/(ico.x+ico.splitx); sd.column++)
     {
     for(sd.counter=0; sd.counter<=3; sd.counter++)
     {
     if(sd.file[(sd.counter+(4*sd.column))][0]!='\0'){if(((cursor.x-(ico.spacex+(ico.spacex*sd.column)))/ico.x==sd.column && ((cursor.y-thm.menu_height)-(ico.spacey+(ico.spacey*sd.counter)))/ico.y==sd.counter && cursor.x>=ico.spacex && cursor.y>=(16+ico.spacey))==0){draw(0,0,48,48,folder0,(ico.x*sd.column)+(ico.spacex*(sd.column+1)),((ico.y*sd.counter)+thm.menu_height)+(ico.spacey*(sd.counter+1)));}else{draw(0,0,48,48,folder1,(ico.x*sd.column)+(ico.spacex*(sd.column+1)),((ico.y*sd.counter)+thm.menu_height)+(ico.spacey*(sd.counter+1)));}print((ico.x*sd.column)+(ico.spacex*(sd.column+1)),(((ico.y*sd.counter)+17)+(ico.spacey*(sd.counter+1)))+(ico.y-8),sd.dis_file[sd.counter+(sd.column*4)],rgb(atoi(clr.red[4]),atoi(clr.grn[4]),atoi(clr.blu[4])));}
     }
     }
     if((cursor.y/thm.menu_height==0 && (cursor.x-EdgeAlign(thm.fullscreen_width,thm.menu_width,1))/thm.menu_width==((thm.fullscreen_width/thm.menu_width)-1))==0){draw(0,0,thm.menu_width,thm.menu_height,sttexit0,(thm.menu_width*((thm.fullscreen_width/thm.menu_width)-1))+EdgeAlign(thm.fullscreen_width,thm.menu_width,1),0);}else {draw(0,0,thm.menu_width,thm.menu_height,sttexit1,(thm.menu_width*((thm.fullscreen_width/thm.menu_width)-1))+EdgeAlign(thm.fullscreen_width,thm.menu_width,1),0);}
BREAK0:
     if(Controller.Buttons & FIRSTCLICK && FIRSTCLICKREADY==1)
     {
                           FIRSTCLICKREADY=0;
if(cursor.y/thm.menu_height==0 && (cursor.x-EdgeAlign(thm.fullscreen_width,thm.menu_width,1))/thm.menu_width==((thm.fullscreen_width/thm.menu_width)-1)){return(-1);}
else
{//not exit
                           sd.column=0;
while(sd.column<thm.fullscreen_width/(ico.x+ico.splitx))
{
sd.counter=0;
while(sd.counter<=3)
{
if((cursor.x-(ico.spacex+(ico.spacex*sd.column)))/ico.x==sd.column && ((cursor.y-thm.menu_height)-(ico.spacey+(ico.spacey*sd.counter)))/ico.y==sd.counter && cursor.x>=ico.spacex && cursor.y>=(thm.menu_height+ico.spacey))
{
if(sd.file[(sd.counter+(sd.column*4))][0]!='\0')
{//not a blank space
if(scePowerGetBatteryLifeTime()%60<1&&scePowerGetBatteryLifeTime()/60==0&&scePowerIsBatteryCharging()==0)
{
InitMessage("Warning: Low Battery","Continuing may lead to the curruption and or loss of files.","Continue","Cancel",2);
if((DisplayMsgbox())==1){FreeUserTheme();goto BREAK0;}//return( 1 );
}
else
{
//DisableGraphics();//I don't know if this will stop the crash, but it's worth a try ;)
FreeUserTheme();
//initGraphics();//This will once again begin the screen setup for displaying graphics ;)
//ConvertProcessorPower();//return to normal state
InitMessage("System","New skin will be applied upon next startup.","OK","",1);
DisplayMsgbox();goto BREAK0;//return(1);
}
}//not a blank space
goto BREAK0;
}
sd.counter++;
}
sd.column++;
}
}//not exit
     }else{if((Controller.Buttons & FIRSTCLICK)==0)FIRSTCLICKREADY=1;}
//L & R
if(Controller.Buttons & PSP_CTRL_LTRIGGER)
{
if(sd.current_page>0)
{sd.page_should_be=sd.current_page-1;SystemDirRead();halt(15);}
}
else
if(Controller.Buttons & PSP_CTRL_RTRIGGER&&(Controller.Buttons & PSP_CTRL_LTRIGGER)==0)
{
if(sd.more_pages_exists==1){sd.page_should_be=sd.current_page+1;SystemDirRead();halt(15);}
}
     AudStatusRespond();
     DrawCursor();
     flipScreen();
     }
return 9;
}
////////////////////////////////////////
//**********************************************************************
////////////////////////////////////////////////////
void ThemesWallpaperHall()
{
     while(1)
     {
             sceCtrlReadBufferPositive(&Controller,1);
     DrawWallpaper();draw(0,0,thm.fullscreen_width,thm.fullscreen_height,mainscreen,0,0);                                    sd.column=0;
     for(sd.column=0; sd.column<thm.fullscreen_width/(ico.x+ico.splitx); sd.column++)
     {
     for(sd.counter=0; sd.counter<=3; sd.counter++){if(sd.file[(sd.counter+(4*sd.column))][0]!='\0'){if(((cursor.x-(ico.spacex+(ico.spacex*sd.column)))/ico.x==sd.column && ((cursor.y-thm.menu_height)-(ico.spacey+(ico.spacey*sd.counter)))/ico.y==sd.counter && cursor.x>=ico.spacex && cursor.y>=(thm.menu_height+ico.spacey))==0){draw(0,0,48,48,Fpic0,(ico.x*sd.column)+(ico.spacex*(sd.column+1)),((ico.y*sd.counter)+thm.menu_height)+(ico.spacey*(sd.counter+1)));}else{draw(0,0,48,48,Fpic1,(ico.x*sd.column)+(ico.spacex*(sd.column+1)),((ico.y*sd.counter)+thm.menu_height)+(ico.spacey*(sd.counter+1)));}print((ico.x*sd.column)+(ico.spacex*(sd.column+1)),(((ico.y*sd.counter)+thm.menu_height)+(ico.spacey*(sd.counter+1)))+(ico.y-8),sd.dis_file[sd.counter+(sd.column*4)],rgb(atoi(clr.red[4]),atoi(clr.grn[4]),atoi(clr.blu[4])));}}
     }
     if((cursor.y/thm.menu_height==0 && (cursor.x-EdgeAlign(thm.fullscreen_width,thm.menu_width,1))/thm.menu_width==((thm.fullscreen_width/thm.menu_width)-1))==0){draw(0,0,thm.menu_width,thm.menu_height,sttexit0,(thm.menu_width*((thm.fullscreen_width/thm.menu_width)-1))+EdgeAlign(thm.fullscreen_width,thm.menu_width,1),0);}else {draw(0,0,thm.menu_width,thm.menu_height,sttexit1,(thm.menu_width*((thm.fullscreen_width/thm.menu_width)-1))+EdgeAlign(thm.fullscreen_width,thm.menu_width,1),0);}
BREAK2:
     if(Controller.Buttons & FIRSTCLICK && FIRSTCLICKREADY==1)
     {
                           FIRSTCLICKREADY=0;
if(cursor.y/thm.menu_height==0 && (cursor.x-EdgeAlign(thm.fullscreen_width,thm.menu_width,1))/thm.menu_width==((thm.fullscreen_width/thm.menu_width)-1)){break;}
else
{//not exit
                           sd.column=0;
while(sd.column<thm.fullscreen_width/(ico.x+ico.splitx))
{
sd.counter=0;
while(sd.counter<=3)
{
if((cursor.x-(ico.spacex+(ico.spacex*sd.column)))/ico.x==sd.column && ((cursor.y-thm.menu_height)-(ico.spacey+(ico.spacey*sd.counter)))/ico.y==sd.counter && cursor.x>=ico.spacex && cursor.y>=(thm.menu_height+ico.spacey)){if(sd.file[(sd.counter+(sd.column*4))][0]!='\0')FreeWallpaper(sd.file[(sd.counter+(sd.column*4))]);goto BREAK2;break;}
sd.counter++;
}
sd.column++;
}
}//not exit
     }else{if((Controller.Buttons & FIRSTCLICK)==0)FIRSTCLICKREADY=1;}
//L & R
if(Controller.Buttons & PSP_CTRL_LTRIGGER)
{
if(sd.current_page>0)
{sd.page_should_be=sd.current_page-1;SystemDirRead();halt(15);}
}
else
if(Controller.Buttons & PSP_CTRL_RTRIGGER&&(Controller.Buttons & PSP_CTRL_LTRIGGER)==0)
{
if(sd.more_pages_exists==1){sd.page_should_be=sd.current_page+1;SystemDirRead();halt(15);}
}
     AudStatusRespond();
     DrawCursor();
     flipScreen();
     }
}
////////////////////////////////////////
//**********************************************************************
////////////////////////////////////////////////////////////////////////
void ThemesHallSystem()
{
     Desktop=0;
 while(1)
 {
         sceCtrlReadBufferPositive(&Controller,1);
         DrawWallpaper();draw(0,0,thm.fullscreen_width,thm.fullscreen_height,mainscreen,0,0);
         if(((cursor.y-thm.menu_height)/ico.y==0 && (cursor.x-(ico.spacex+(ico.spacex*0)))/ico.x==0 && cursor.x>=ico.spacex && cursor.y>=(thm.menu_height+ico.spacey))==0)draw(0,0,48,48,sttnwallpaper0,(ico.x*0)+(ico.spacex*1),((ico.y*0)+thm.menu_height)+(ico.spacey*1));else draw(0,0,48,48,sttnwallpaper1,(ico.x*0)+(ico.spacex*1),((ico.y*0)+thm.menu_height)+(ico.spacey*1));
         if(((cursor.y-thm.menu_height)/ico.y==0 && (cursor.x-(ico.spacex+(ico.spacex*1)))/ico.x==1 && cursor.x>=ico.spacex && cursor.y>=(thm.menu_height+ico.spacey))==0)draw(0,0,48,48,sttnsettings0,(ico.x*1)+(ico.spacex*2),((ico.y*0)+thm.menu_height)+(ico.spacey*1));else draw(0,0,48,48,sttnsettings1,(ico.x*1)+(ico.spacex*2),((ico.y*0)+thm.menu_height)+(ico.spacey*1));
         if(((cursor.y-thm.menu_height)/ico.y==0 && (cursor.x-(ico.spacex+(ico.spacex*2)))/ico.x==2 && cursor.x>=ico.spacex && cursor.y>=(thm.menu_height+ico.spacey))==0)draw(0,0,48,48,sttnsettings0,(ico.x*2)+(ico.spacex*3),((ico.y*0)+thm.menu_height)+(ico.spacey*1));else draw(0,0,48,48,sttnsettings1,(ico.x*2)+(ico.spacex*3),((ico.y*0)+thm.menu_height)+(ico.spacey*1));
         if((cursor.y/thm.menu_height==0 && (cursor.x-EdgeAlign(thm.fullscreen_width,thm.menu_width,1))/thm.menu_width==((thm.fullscreen_width/thm.menu_width)-1))==0){draw(0,0,thm.menu_width,thm.menu_height,sttexit0,(thm.menu_width*((thm.fullscreen_width/thm.menu_width)-1))+EdgeAlign(thm.fullscreen_width,thm.menu_width,1),0);}else {draw(0,0,thm.menu_width,thm.menu_height,sttexit1,(thm.menu_width*((thm.fullscreen_width/thm.menu_width)-1))+EdgeAlign(thm.fullscreen_width,thm.menu_width,1),0);}
         if(Controller.Buttons & FIRSTCLICK && FIRSTCLICKREADY==1)
         {
                               FIRSTCLICKREADY=0;
                               if(cursor.y/thm.menu_height==0 && (cursor.x-EdgeAlign(thm.fullscreen_width,thm.menu_width,1))/thm.menu_width==((thm.fullscreen_width/thm.menu_width)-1)){Desktop=1;break;}
                               else
                               {//not exit
                               if((cursor.y-(thm.menu_height+ico.spacey))/ico.y==0)
                               { 
                               if((cursor.x-(ico.spacex+(ico.spacex*0)))/ico.x==0 && cursor.x>=ico.spacex){sprintf(sd.dir,"ms0:/XT1-OS/System/Resources/Wallpaper/");sd.category=2;SystemDirRead();ThemesWallpaperHall();}
                               if((cursor.x-(ico.spacex+(ico.spacex*1)))/ico.x==1 && cursor.x>=ico.spacex){sprintf(sd.dir,"ms0:/XT1-OS/System/Resources/Themes/");sd.category=1;SystemDirRead();ThemesSchemeHall();}
                               }
                               }//not exit
         }else{if((Controller.Buttons &FIRSTCLICK)==0)FIRSTCLICKREADY=1;}
         AudStatusRespond();
         DrawCursor();
         flipScreen();
 }
}
////////////////////////////////////////////////////////////////////////
////////////////////////RIGHT_CLICK
void RightClick()
{
//nothing yet...
/*
InitMessage("System","This is a MsgBox(), Got it?","Yes","No",2);
if((DisplayMsgbox())==2){InitMessage("Dumba$s","Too bad!!","OK","",1);DisplayMsgbox();}else{}
InitMessage("System","This is a single buttn.","OK","",1);
if((DisplayMsgbox())==1){}else{}
*/
}
////////////////////////RIGHT_CLICK
void LeftClick()
{
     //DesktopFeature:Time
while(1)
{
 if(cursor.x>=thm.fullscreen_width-41 && cursor.y>=thm.fullscreen_height-17){if(DesktopFeatures==1)DesktopFeatures=0; else DesktopFeatures=1;break;}//desktop time
 if(cursor.x>=thm.fullscreen_width-66 && cursor.x<=thm.fullscreen_width-42 && cursor.y>=thm.fullscreen_height-17){if(DesktopFeatures==2)DesktopFeatures=0; else DesktopFeatures=2;break;}//desktop battery
 if(cursor.x<=thm.startbutton_width && cursor.y>=thm.fullscreen_height-thm.startbutton_height){Start=Start*(-1);if(Start==1){sprintf(Directory,"ms0:/PSP/");start.page_should_be=0;start.current_page=0;StartList();}break;}//startmenu
 if(Start==1 && cursor.x<132 && cursor.y<thm.fullscreen_height-(18+2) && cursor.y>=34)
{
if(((lround((thm.fullscreen_height-cursor.y)/13.0769))-2)<16)
{//16
if(((lround((thm.fullscreen_height-cursor.y)/13.0769))-2)==0 && start.more_pages_exists==1){start.page_should_be=start.current_page+1;StartList();}
else
if((start.type[((lround((thm.fullscreen_height-cursor.y)/13.0769))-2)])==0)
{
sprintf(DirectoryAdd,"%s",Directory);
sprintf(Directory,"%s%s/",DirectoryAdd,start.item[((lround((thm.fullscreen_height-cursor.y)/13.0769))-2)]);
start.current_page=0;//because it is a new folder we're moving to :)
StartList();DirectoryAdd[0]='\0';
}else
if((start.type[((lround((thm.fullscreen_height-cursor.y)/13.0769))-2)])!=-1)
{sprintf(FileHold,"%s",Directory);
sprintf(FileAdd,"%s",start.item[((lround((thm.fullscreen_height-cursor.y)/13.0769))-2)]);
ActivateFile();}
}//16
else//if item status math is equal to 16 it must go back
{//16
if(((lround((thm.fullscreen_height-cursor.y)/13.0769))-2)==16){if(start.current_page<=0){Directory[GoBack(Directory)]='\0';StartList();}
else{start.page_should_be=start.current_page-1;StartList();}}
}//16end else if it's not a item below 16 -------- :)
break;
}//end if x is correct
if (Start==1 && cursor.x>=132 && cursor.x<=183 && cursor.y>=(16+(31*1)))
{//if xright is correct!
 if((cursor.y-(16+0))/20==1)
 {
 if(fld.ProgramsRunningC<4)
{//it's ok
 fld.ProgramsRunningC++;
 ProgramsRunningC++;
 fld.active=Find_Open_Folder();
 Prepare_Depth(d.depth,1);
 fld.depth[fld.active]=0;
 fld.start=1;
 fld.page_should_be[fld.active]=start.current_page;
 fld.fullscreen[fld.active]=0;
 Browse(Directory);
 fld.show[fld.active]=1;
}//it's ok
 }//call folder browser
 else
 if((cursor.y-(16+0))/31==2){SettingsHallSystem();}
 else
 if((cursor.y-(16+0))/31==3){ThemesHallSystem();}
 else
 if((cursor.y-(16+0))/31==7)
 {
                        InitMessage("Shutdown","Reboot* Soon... Maybe!","Shutdown","Cancel",2);
                        if((DisplayMsgbox())==1){scePowerSetClockFrequency(222,222,111);MP3_End();halt(1);sceKernelExitGame();}else{}
 }
 break;
}//if xright is correct!
if(aud.show==1){if(aud.size!=1){if(cursor.x>=aud.x && cursor.x<=aud.x+thm.mtopbar_width && cursor.y>=aud.y && cursor.y<=aud.y+thm.mtopbar_height){Audio_ButtnChk();break;}}else {if(cursor.x>=aud.x && cursor.x<=aud.x+thm.mtopbar_width && cursor.y>=aud.y && cursor.y<=aud.y+(thm.mtopbar_height+thm.mwindow_height)){Audio_ButtnChk();break;}}}
//loop for directories, text, and pictures!! :)
//DYNAMIC WINDOWING ATTEMPT ;)
if((txt.ProgramsRunningC>-1||fld.ProgramsRunningC>-1)&&d.depth>-1)
{//ANY EXISTS
int Selection_Found=0;
int check_windows=1;
D1:
if(check_windows!=0)
                    {//allow
for(d.count=0; d.count<=d.depth; d.count++)//check depth
{//check
 for(d.counter=0; d.counter<=4; d.counter++)//check windows
                    {//DEPTH LOOPZ
//FOLDERS
if(fld.depth[d.counter]==d.count&&fld.show[d.counter]==1)
 {//IF 1
 if(cursor.x>=fld.x[d.counter]&&cursor.x<=fld.x[d.counter]+304&&cursor.y>=fld.y[d.counter]&&cursor.y<=fld.y[d.counter]+176)
 {
 fld.active=d.counter;Prepare_Depth(fld.depth[fld.active]-1,0);fld.depth[fld.active]=0;
 Folder_ButtnChk();Selection_Found++;check_windows=0;goto D1;
 }
 }//IF 1
 else
//TEXT
 if(txt.depth[d.counter]==d.count&&txt.show[d.counter]==1)
 {//IF 2
 if(cursor.x>=txt.x[d.counter]&&cursor.x<=txt.x[d.counter]+320&&cursor.y>=txt.y[d.counter]&&cursor.y<=txt.y[d.counter]+212)
 {
 txt.active=d.counter;Prepare_Depth(txt.depth[txt.active]-1,0);txt.depth[txt.active]=0;
 Notepad_ButtnChk();Selection_Found++;check_windows=0;goto D1;
 }
 }//IF 2
                    }//DEPTH LOOPZ
}//check
                    }//allow
if(Selection_Found>0){Selection_Found=0;break;}
}//ANY EXISTS
////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////NOTEPAD CHECKING IN "ORDER DRAWING" FOR DYNAMIC SELECTION!!
break;//here if nothing is activated ;)
}//end while event!!
}//end function
//////////////////////
pspDebugScreenSetTextColor(rgb(255,0,0));
dprint("Done!");halt(9);
////////////////////
ConvertProcessorPower();
////////////////////
clearDebug();
initGraphics();

while(1)
{
sceCtrlReadBufferPositive(&Controller,1);
AudStatusRespond();
if(Desktop==1 || Start==1){DrawDesktop();DrawBattery();DrawTime();DrawCursor();}
if(Controller.Buttons & PSP_CTRL_HOME){InitMessage("System","Accessing the *Home key    develops errors, please usethe supplied method.","OK","",1);DisplayMsgbox();}
if(Controller.Buttons & PSP_CTRL_SELECT){KrnlMode=KrnlMode*(-1);FixControllerMode();halt(15);}
if(Controller.Buttons & PSP_CTRL_START && STARTPRESSREADY==1 && Desktop==1){STARTPRESSREADY=0;if(Start!=1){sprintf(Directory,"ms0:/PSP/");start.page_should_be=0;start.current_page=0;cursor.x=42;cursor.y=thm.fullscreen_height-9;Start=1;StartList();}else{Start=-1;}/*halt(12);continue;*/}else {if((Controller.Buttons & PSP_CTRL_START)==0)STARTPRESSREADY=1;}
//if(Controller.Buttons & PSP_CTRL_TRIANGLE){Force.uiPress &PSP_CTRL_START;}//THIS WAS JUST A TEST TO TRY TO FORCE KEY PRESSES :( IT FAILED!!

if(Controller.Buttons & FIRSTCLICK && FIRSTCLICKREADY==1){FIRSTCLICKREADY=0;LeftClick();/*continue;*/}else{/*REPAIR ALL CARRY EVENTS!!*/if((Controller.Buttons & FIRSTCLICK)==0){if(aud.carry==1){aud.carry=0;}if(msg.carry==1){msg.carry=0;}if(vid.carry==1){vid.carry=0;}for(counter=0; counter<6; counter++){if(txt.carry[counter]==1){txt.carry[counter]=0;}if(fld.carry[counter]==1){fld.carry[counter]=0;}}FIRSTCLICKREADY=1;}}
if(Controller.Buttons & SECONDCLICK && SECONDCLICKREADY==1){SECONDCLICKREADY=0;RightClick();}else{if((Controller.Buttons & SECONDCLICK)==0){if(SECONDCLICKREADY!=1)SECONDCLICKREADY=1;}}
if(Controller.Buttons & PSP_CTRL_LTRIGGER){LoadAndStartModule_PRX("ms0:/XT1_Module.prx", 0);}//parent directory we are from :)
//if(Controller.Buttons & PSP_CTRL_RTRIGGER){ExecuteUmd();}//last directory we were in :)
//if(Controller.Buttons & PSP_CTRL_HOLD){if(Standby==1){PowerDown();continue;}else{print((thm.fullscreen_width/2)-(8*4),((thm.fullscreen_height-18)/2)+(8/2),"-Locked-",rgb(atoi(clr.red[6]),atoi(clr.grn[6]),atoi(clr.blu[6])));}}
//if(Controller.Buttons & PSP_CTRL_LTRIGGER){char temporaryvariable2[50];sprintf(temporaryvariable2,"%i -- %i",start.current_page,aud.show);print(240,140,temporaryvariable2,rgb(0,0,0));}
/*char temp[10];sprintf(temp,"%i",fldback0->imageWidth);
if(Controller.Buttons & PSP_CTRL_LTRIGGER){print(240,120,temp,rgb(255,0,0));}
sprintf(temp,"%i",Faud0->imageWidth);
if(Controller.Buttons & PSP_CTRL_TRIANGLE){print(240,120,temp,rgb(255,0,0));}
*/
//if(Controller.Buttons & PSP_CTRL_SQUARE){char*exttemp;exttemp=strrchr(aud.currently_playing,'.');print(240,120,exttemp,rgb(0,255,0));}
//if(Controller.Buttons & PSP_CTRL_SQUARE){InitMessage("Testing","Just Wanted To See If This Works...","OK","",1);DisplayMsgbox();}
//if(Controller.Buttons & PSP_CTRL_RTRIGGER){for(txt.count=0; txt.count<=5; txt.count++){txt.active=-1;txt.x[txt.count]=16*4;txt.y[txt.count]=lround(16*(((thm.fullscreen_height-208)/16)/2));txt.show[txt.count]=0;}}
//if(Controller.Buttons & PSP_CTRL_RTRIGGER){char temporaryvariable[50];sprintf(temporaryvariable,"%i",start.type[((lround((thm.fullscreen_height-cursor.y)/13.0769))-1)]);print(240,140,temporaryvariable,rgb(0,0,0));}
//LastButton=Controller.Buttons;//LAST BUTTON IS AN INTEGER CREATED ABOVE :)
flipScreen();
}
//return main
return 0;
}//end main()
