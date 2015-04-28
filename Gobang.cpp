//this game is created by Like HU and Yi Man

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
#include<stdlib.h>


using namespace std;

class Gobang{

      private:

             int chessboard[15][15];          //Chessboard
             int five[5][5];                  //5*5Chessboard
             int six[6][6];
             int computernum,humannum;         //number of pieces
             int p1,p2;                       //number of pieces
             int last1,last2;                    //record last step
             int comresults[15][15];             //save score
             int humresults[15][15];
             int temp[15][15];             //temp Chessboard
             int max_com,max_hum,max_com_i,max_com_j,max_hum_i,max_hum_j;           //saving the highest points of computer's and player's
             int total_com,total_hum;              //computer's total score and player's total score.
             int goback;                      //back to start menu.


      public:

              Gobang();
              void setchessboard(int ,int,int);     //change chessboard
              void count();                         //count number of pieces
              void count_total();                //count total score
              void save(int);                     //store game
              int dir();                         //show games which has already stored
              void firstgo();                  //computer go first
              void print(int n);              //show chessboard
              void input(int n);              //input
              void getfive(int i,int j);             // read the data in 5*5 Chessboard
              void getsix(int,int);
              int ifwin();
              void think();
              void getresults();
              void r_four();
              void r_three();
              void r_two();
              int returngoback();


};



Gobang::Gobang(){
                 for(int i=0;i<15;i++)
                         for(int j=0;j<15;j++){
                                chessboard[i][j]=0;
                                temp[i][j]=0;
                                comresults[i][j]=0;
                                humresults[i][j]=0;}

                 for(int i=0;i<5;i++)
                         for(int j=0;j<5;j++)
                                {five[i][j]=0;}
                 computernum=0;
                 humannum=0;
                 p1=0;p2=0;
                 last1=-1;last2=-1;       //-1 means the game is not start
                 max_com=0;max_hum=0;max_com_i=0;
                 max_com_j=0;max_hum_i=0;max_hum_j=0;
                 total_com=0;total_hum=0;
                 goback=0;
}



void Gobang::setchessboard(int i,int j,int n){
     chessboard[i][j]=n;}


void Gobang::count(){
     computernum=0;
     humannum=0;
     for(int i=0;i<15;i++)
         for(int j=0;j<15;j++){
                 if(chessboard[i][j]==1) computernum++;
                 if(chessboard[i][j]==2) humannum++;
                 p1=computernum;p2=humannum;
                 }
}



//count the total scores of computer and players .

void Gobang::count_total(){

     total_com=0;total_hum=0;
     for(int i=0;i<15;i++)
            for(int j=0;j<15;j++){
                    comresults[i][j]=0;
                    humresults[i][j]=0;}                //clean


       //mark the point
       r_four();
       r_three();
       r_two();

       //Calculate the scores of player and computer separately
       for(int i=0;i<15;i++)
            for(int j=0;j<15;j++){
                    total_com+=comresults[i][j];
                    total_hum+=humresults[i][j];
                    }



       //if next piece will win.
     for(int i=0;i<15;i++){
         for(int j=0;j<15;j++){
                 if(chessboard[i][j]!=0) continue;       //find empty space
                  chessboard[i][j]=1;
                  if(ifwin()==1) {total_com+=1000;}                  //computer win
                  chessboard[i][j]=0;                      //useless space no pieces
                  }
         }

     for(int i=0;i<15;i++){
         for(int j=0;j<15;j++){
                 if(chessboard[i][j]!=0) continue;       //find empty space
                  chessboard[i][j]=2;
                  if(ifwin()==2) {total_hum+=1000;}                  //player win
                  chessboard[i][j]=0;
                  }
         }

}


//store game

void Gobang::save(int n){                                  //n=1means play with computer ，n=2play with player
          string filename;
          cin>>filename;
          filename=filename+".gbg";
          ofstream ofile(filename.c_str());
          ofile<<n<<endl;
          for(int i=0;i<15;i++)
              for(int j=0;j<15;j++){
                      ofile<<chessboard[i][j]<<endl;
                      }
          ofile.close();
          cout<<"thie game is stored in “"<<filename<<"file”"<<endl;
}


//show

int Gobang::dir(){
     system("dir/b>dir.txt");
     ifstream ifile("dir.txt");
     string filename;
     int num=0;
     while(ifile>>filename){
              if(filename.find(".gbg")!=-1) {
                                             cout<<filename<<endl;
                                             num++;
                                             }
              }
    cout<<"there are"<<num<<"files"<<endl;
    return num;
}


int Gobang::returngoback(){
    return goback;
}


//computer first

void Gobang::firstgo(){
     chessboard[8][8]=1;
     last1=8,last2=8;
     }


//show

void Gobang::print(int n){
     system("cls");
     count();
     count_total();
     cout<<"****************Gobang****************"<<endl;
     cout<<"                      2015.4.14"<<endl;
     if(n==1){
              cout<<"status of pieces: - empty * computer o player"<<endl;
             cout<<"number of pieces:  computer:"<<setw(4)<<computernum<<" player:"<<setw(4)<<humannum<<endl;
             cout<<"total scores:  computer:"<<setw(4)<<total_com<<" player: "<<setw(4)<<total_hum<<endl;
             }
     if(n==2) {
              cout<<"status of pieces: - empty  * player 1 o player2."<<endl;
             cout<<"number of pieces:    player 1:"<<setw(4)<<p1<<" player 2:"<<setw(4)<<p2<<endl;
             cout<<"total score:    player 1: "<<setw(4)<<total_com<<" player 2:"<<setw(4)<<total_hum<<endl;
             }
     cout<<"row/column"<<endl;
     cout<<"  ";
     for(int i=0;i<15;i++){
             cout<<setw(3)<<i;}
     cout<<endl;
     for(int i=0;i<15;i++)
            {
             cout<<setw(3)<<i;
             for(int j=0;j<15;j++)
                    {
                     if(chessboard[i][j]==0) cout<<" - ";
                     if(chessboard[i][j]==1) cout<<" * ";
                     if(chessboard[i][j]==2) cout<<" o ";
                     }
             cout<<endl;
             }
     if(last1!=-1) {
                   if(n==1) cout<<"status of computer's piece: "<<last1<<"  "<<last2<<endl;
                   if(n==2) cout<<"status of player's piece "<<last1<<"  "<<last2<<endl;
                   }
      else cout<<"last step of piece : empty"<<endl;
     cout<<"input the row/column to put piece: "<<endl;
}




void Gobang::input(int n){
     if(n==1)
     while(1){
     int i,j;
     cin>>i;
     if(i==111) {cout<<"store this game or not? y/n"<<endl;
                  char yn;cin>>yn;
                  if(yn=='y'){
                              save(1);
                             cout<<"this game has already stored , keep playing the game!"<<endl;
                             }
                  if(yn=='n') cout<<"this game has not stored, keep playing the game!"<<endl;
                  cin>>i>>j;
                  }
     else if(i==222) {goback=1;return;}
     else cin>>j;
     if(!(i>=0&&i<15)) {
                       cout<<"error input !beyond the range of the chessboard! please input again"<<endl;
                       continue;
                       }
     else if(!(j>=0&&j<15)) {
                       cout<<"error input !beyond the range of the chessboard! please input again"<<endl;
                       continue;
                       }
     else if(chessboard[i][j]!=0){
                             cout<<"error input !this place has already put the piece! please input again"<<endl;
                             continue;
                             }
     else{chessboard[i][j]=2;
         last1=i;last2=j;
         humannum++;
         break;
         }

     }
     if(n==2){
     while(1){
              cout<<"player 1 to put the piece:"<<endl;
              int i,j;
              cin>>i;
               if(i==111) {cout<<"store this game or not? y/n"<<endl;
                  char yn;cin>>yn;
                  if(yn=='y') {
                              save(2);
                               cout<<"this game has already stored , keep playing the game!"<<endl;
                               }
                  if(yn=='n') cout<<"this game has not stored, keep playing the game!"<<endl;
                  cin>>i>>j;
                  }
              else if(i==222) {goback=1;return;}
              else cin>>j;
              if(!(i>=0&&i<15)) {
                       cout<<"Wrong number! Over the chess board's boundary! Please re-enter the number."<<endl;
                       continue;
                       }
              else if(!(j>=0&&j<15)) {
                       cout<<"Wrong number! Over the chess board's boundary! Please re-enter the number."<<endl;
                       continue;
                       }
              else if(chessboard[i][j]!=0){
                             cout<<"Wrong number! This place already has stone! Please re-enter the number."<<endl;
                             continue;
                             }
              else{chessboard[i][j]=1;
                  p1++;
                  last1=i;last2=j;
                  break;
                   }
              }
              print(2);
      while(1){
              cout<<"Player2's turn:"<<endl;
              int i,j;
              cin>>i>>j;
              if(!(i>=0&&i<15)) {
                       cout<<"Wrong number! Over the chess board's boundary! Please re-enter the number."<<endl;
                       continue;
                       }
              else if(!(j>=0&&j<15)) {
                       cout<<"Wrong number! Over the chess board's boundary! Please re-enter the number."<<endl;
                       continue;
                       }
              else if(chessboard[i][j]!=0){
                             cout<<"Wrong number! This place already has stone! Please re-enter the number."<<endl;
                             continue;
                             }
              else{chessboard[i][j]=2;
                  p2++;
                  last1=i;last2=j;
                  break;
                   }
     }
     }


}




void Gobang::getfive(int i,int j){
     for(int m=0;m<5;m++)
         for(int n=0;n<5;n++)
                 five[m][n]=chessboard[m+i][n+j];
}



void Gobang::getsix(int i,int j){
     for(int m=0;m<6;m++)
         for(int n=0;n<6;n++)
                 six[m][n]=chessboard[m+i][n+j];
}


//determine whether anyone Win
int Gobang::ifwin(){
    for(int i=0;i<=10;i++)
        for(int j=0;j<=10;j++){
              getfive(i,j);
              for(int m=0;m<5;m++){
                      if(five[m][0]==1&&five[m][1]==1&&five[m][2]==1&&five[m][3]==1&&five[m][4]==1)
                          return (1);
                      if(five[0][m]==1&&five[1][m]==1&&five[2][m]==1&&five[3][m]==1&&five[4][m]==1)
                          return (1);}
              if(five[0][0]==1&&five[1][1]==1&&five[2][2]==1&&five[3][3]==1&&five[4][4]==1)
                   return (1);
              if(five[0][4]==1&&five[1][3]==1&&five[2][2]==1&&five[3][1]==1&&five[4][0]==1)
                   return (1);
              }

    for(int i=0;i<=10;i++)
        for(int j=0;j<=10;j++){
              getfive(i,j);
              for(int m=0;m<5;m++){
                      if(five[m][0]==2&&five[m][1]==2&&five[m][2]==2&&five[m][3]==2&&five[m][4]==2)
                          return 2;
                      if(five[0][m]==2&&five[1][m]==2&&five[2][m]==2&&five[3][m]==2&&five[4][m]==2)
                          return 2;}
              if(five[0][0]==2&&five[1][1]==2&&five[2][2]==2&&five[3][3]==2&&five[4][4]==2)
                   return 2;
              if(five[0][4]==2&&five[1][3]==2&&five[2][2]==2&&five[3][1]==2&&five[4][0]==2)
                   return 2;
              }

    return 0;
}


//Computer thinking
void Gobang::think(){

     total_com=0;total_hum=0;

     //first determine if the next step will win
     for(int i=0;i<15;i++){
         for(int j=0;j<15;j++){
                 if(chessboard[i][j]!=0) continue;       //find unused place
                  chessboard[i][j]=1;
                  if(ifwin()==1) {last1=i;last2=j;return;}                  //computer win
                  chessboard[i][j]=0;                      //do not place stone on useless place
                  }
         }

     for(int i=0;i<15;i++){
         for(int j=0;j<15;j++){
                 if(chessboard[i][j]!=0) continue;       //find unused place
                  chessboard[i][j]=2;
                  if(ifwin()==2) {chessboard[i][j]=1;last1=i;last2=j;return;}                  //stop player to win
                  chessboard[i][j]=0;                      //do not place stone on useless place
                  }
         }




      //the first step from computer and avoid the boundary.
      if(computernum==0) {
                         if(last1<=2&&chessboard[last1+1][last2]==0)
                            {chessboard[last1+1][last2]=1;last1++;return; }
                               else if(last1>=12&&chessboard[last1-1][last2]==0)
                                     {chessboard[last1-1][last2]=1;last1--;return;}
                                        else if(last2<=2&&chessboard[last1][last2+1]==0)
                                            {chessboard[last1][last2+1]=1;last2++;return;}
                                                else if(last2>=12&&chessboard[last1][last2-1]==0)
                                                     {chessboard[last1][last2-1]=1;last2--;return;}
                                                        else if(chessboard[last1+1][last2]==0)
                                                           {chessboard[last1+1][last2]=1;last1++;return;}
                                                                  else if(chessboard[last1-1][last2]==0)
                                                                        {chessboard[last1-1][last2]=1;last1--;return;}
                                                                          else if(chessboard[last1][last2+1]==0)
                                                                                  {chessboard[last1][last2+1]=1;last2++;return;}
                                                                                       else if(chessboard[last1][last2-1]==0)
                                                                                                {chessboard[last1][last2-1]=1;last2--;return;}
                         }




   getresults();




}



void Gobang::getresults(){

          for(int i=0;i<15;i++)
            for(int j=0;j<15;j++){
                    comresults[i][j]=0;
                    humresults[i][j]=0;}                //return 0 before start.
       max_com=0;max_hum=0;max_com_i=0;
       max_com_j=0;max_hum_i=0;max_hum_j=0;


       //start score
       r_four();
       r_three();
       r_two();

       //select the highest score from  computer and player
       for(int i=0;i<15;i++)
            for(int j=0;j<15;j++){
                    if(comresults[i][j]>max_com){
                                                 max_com=comresults[i][j];
                                                 max_com_i=i;
                                                 max_com_j=j;
                                                 }
                    if(humresults[i][j]>max_hum){
                                                 max_hum=humresults[i][j];
                                                 max_hum_i=i;
                                                 max_hum_j=j;
                                                 }
                    }

       //analysis the highest score and to determine attack or defend

       if(max_com>=1000) {                                      //computer can form 4
                       chessboard[max_com_i][max_com_j]=1;
                       last1=max_com_i;last2=max_com_j;
                       return;
                       }
       if(max_hum>=1000) {                                      //stop player when have 4 stones on one line
                       chessboard[max_hum_i][max_hum_j]=1;
                       last1=max_hum_i;last2=max_hum_j;
                       return;
                       }

       if(max_com>=18) {                                      //computer can forms double 3 or more
                       chessboard[max_com_i][max_com_j]=1;
                       last1=max_com_i;last2=max_com_j;
                       return;
                       }
       if(max_hum>=18) {                                      //stop player to form double 3 situation
                       chessboard[max_hum_i][max_hum_j]=1;
                       last1=max_hum_i;last2=max_hum_j;
                       return;
                       }


       if(max_com==17||max_com==16) {
                       chessboard[max_com_i][max_com_j]=1;
                       last1=max_com_i;last2=max_com_j;
                       return;
                       }
       if(max_hum==17||max_hum==16) {
                       chessboard[max_hum_i][max_hum_j]=1;
                       last1=max_hum_i;last2=max_hum_j;
                       return;
                       }


       if(max_com<16&&max_com>=10) {
                       chessboard[max_com_i][max_com_j]=1;
                       last1=max_com_i;last2=max_com_j;
                       return;
                       }
       if(max_hum<16&&max_hum>=10) {
                       chessboard[max_hum_i][max_hum_j]=1;
                       last1=max_hum_i;last2=max_hum_j;
                       return;
                       }

       //other situation computer will ignore player's step and choose the best place.
       chessboard[max_com_i][max_com_j]=1;
       last1=max_com_i;last2=max_com_j;
       return;
}




void Gobang::r_four(){

     for(int i=1;i<14;i++)
         for(int j=1;j<14;j++){

                 if(chessboard[i][j]!=0) continue;


                 //the 1st situation   xooo@x

                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==1&&chessboard[i][j-2]==1&&chessboard[i][j-3]==1&&chessboard[i][j-4]==0) comresults[i][j]+=100;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==1&&chessboard[i-4][j-4]==0) comresults[i][j]+=100;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==1&&chessboard[i-2][j]==1&&chessboard[i-3][j]==1&&chessboard[i-4][j]==0) comresults[i][j]+=100;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==1&&chessboard[i-4][j+4]==0) comresults[i][j]+=100;
                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==1&&chessboard[i][j+2]==1&&chessboard[i][j+3]==1&&chessboard[i][j+4]==0) comresults[i][j]+=100;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==1&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==1&&chessboard[i+4][j+4]==0) comresults[i][j]+=100;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==1&&chessboard[i+2][j]==1&&chessboard[i+3][j]==1&&chessboard[i+4][j]==0) comresults[i][j]+=100;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==1&&chessboard[i+4][j-4]==0) comresults[i][j]+=100;

                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==2&&chessboard[i][j-2]==2&&chessboard[i][j-3]==2&&chessboard[i][j-4]==0) humresults[i][j]+=100;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==2&&chessboard[i-4][j-4]==0) humresults[i][j]+=100;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==2&&chessboard[i-2][j]==2&&chessboard[i-3][j]==2&&chessboard[i-4][j]==0) humresults[i][j]+=100;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==2&&chessboard[i-4][j+4]==0) humresults[i][j]+=100;
                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==2&&chessboard[i][j+2]==2&&chessboard[i][j+3]==2&&chessboard[i][j+4]==0) humresults[i][j]+=100;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==2&&chessboard[i+2][j+2]==2&&chessboard[i+3][j+3]==2&&chessboard[i+4][j+4]==0) humresults[i][j]+=100;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==2&&chessboard[i+2][j]==2&&chessboard[i+3][j]==2&&chessboard[i+4][j]==0) humresults[i][j]+=100;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==2&&chessboard[i+4][j-4]==0) humresults[i][j]+=100;


                 //the 2nd situation  xoo@ox

                 if(chessboard[i][j+2]==0&&chessboard[i][j+1]==1&&chessboard[i][j-1]==1&&chessboard[i][j-2]==1&&chessboard[i][j-3]==0) comresults[i][j]+=100;
                 if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==1&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==0) comresults[i][j]+=100;
                 if(chessboard[i+2][j]==0&&chessboard[i+1][j]==1&&chessboard[i-1][j]==1&&chessboard[i-2][j]==1&&chessboard[i-3][j]==0) comresults[i][j]+=100;
                 if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==1&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==0) comresults[i][j]+=100;
                 if(chessboard[i][j-2]==0&&chessboard[i][j-1]==1&&chessboard[i][j+1]==1&&chessboard[i][j+2]==1&&chessboard[i][j+3]==0) comresults[i][j]+=100;
                 if(chessboard[i-2][j-2]==0&&chessboard[i-1][j-1]==1&&chessboard[i+1][j+1]==1&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==0) comresults[i][j]+=100;
                 if(chessboard[i-2][j]==0&&chessboard[i-1][j]==1&&chessboard[i+1][j]==1&&chessboard[i+2][j]==1&&chessboard[i+3][j]==0) comresults[i][j]+=100;
                 if(chessboard[i-2][j+2]==0&&chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==0) comresults[i][j]+=100;

                 if(chessboard[i][j+2]==0&&chessboard[i][j+1]==2&&chessboard[i][j-1]==2&&chessboard[i][j-2]==2&&chessboard[i][j-3]==0) humresults[i][j]+=100;
                 if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==2&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==0) humresults[i][j]+=100;
                 if(chessboard[i+2][j]==0&&chessboard[i+1][j]==2&&chessboard[i-1][j]==2&&chessboard[i-2][j]==2&&chessboard[i-3][j]==0) humresults[i][j]+=100;
                 if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==2&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==0) humresults[i][j]+=100;
                 if(chessboard[i][j-2]==0&&chessboard[i][j-1]==2&&chessboard[i][j+1]==2&&chessboard[i][j+2]==2&&chessboard[i][j+3]==0) humresults[i][j]+=100;
                 if(chessboard[i-2][j-2]==0&&chessboard[i-1][j-1]==2&&chessboard[i+1][j+1]==2&&chessboard[i+2][j+2]==2&&chessboard[i+3][j+3]==0) humresults[i][j]+=100;
                 if(chessboard[i-2][j]==0&&chessboard[i-1][j]==2&&chessboard[i+1][j]==2&&chessboard[i+2][j]==2&&chessboard[i+3][j]==0) humresults[i][j]+=100;
                 if(chessboard[i-2][j+2]==0&&chessboard[i-1][j+1]==2&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==0) humresults[i][j]+=100;





                 //the 3rd situation     *ooo@x

                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==1&&chessboard[i][j-2]==1&&chessboard[i][j-3]==1&&chessboard[i][j-4]==2) comresults[i][j]+=11;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==1&&chessboard[i-4][j-4]==2) comresults[i][j]+=11;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==1&&chessboard[i-2][j]==1&&chessboard[i-3][j]==1&&chessboard[i-4][j]==2) comresults[i][j]+=11;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==1&&chessboard[i-4][j+4]==2) comresults[i][j]+=11;
                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==1&&chessboard[i][j+2]==1&&chessboard[i][j+3]==1&&chessboard[i][j+4]==2) comresults[i][j]+=11;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==1&&chessboard[i+1][j+2]==1&&chessboard[i+3][j+3]==1&&chessboard[i+4][j+4]==2) comresults[i][j]+=11;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==1&&chessboard[i+2][j]==1&&chessboard[i+3][j]==1&&chessboard[i+4][j]==2) comresults[i][j]+=11;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==1&&chessboard[i+4][j-4]==2) comresults[i][j]+=11;

                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==2&&chessboard[i][j-2]==2&&chessboard[i][j-3]==2&&chessboard[i][j-4]==1) humresults[i][j]+=11;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==2&&chessboard[i-4][j-4]==1) humresults[i][j]+=11;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==2&&chessboard[i-2][j]==2&&chessboard[i-3][j]==2&&chessboard[i-4][j]==1) humresults[i][j]+=11;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==2&&chessboard[i-4][j+4]==1) humresults[i][j]+=11;
                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==2&&chessboard[i][j+2]==2&&chessboard[i][j+3]==2&&chessboard[i][j+4]==1) humresults[i][j]+=11;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==2&&chessboard[i+1][j+2]==2&&chessboard[i+3][j+3]==2&&chessboard[i+4][j+4]==1) humresults[i][j]+=11;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==2&&chessboard[i+2][j]==2&&chessboard[i+3][j]==2&&chessboard[i+4][j]==1) humresults[i][j]+=11;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==2&&chessboard[i+4][j-4]==1) humresults[i][j]+=11;

                 //the 4th situation   *oo@ox

                 if(chessboard[i][j+2]==0&&chessboard[i][j+1]==1&&chessboard[i][j-1]==1&&chessboard[i][j-2]==1&&chessboard[i][j-3]==2) comresults[i][j]+=11;
                 if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==1&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==2) comresults[i][j]+=11;
                 if(chessboard[i+2][j]==0&&chessboard[i+1][j]==1&&chessboard[i-1][j]==1&&chessboard[i-2][j]==1&&chessboard[i-3][j]==2) comresults[i][j]+=11;
                 if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==1&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==2) comresults[i][j]+=11;
                 if(chessboard[i][j-2]==0&&chessboard[i][j-1]==1&&chessboard[i][j+1]==1&&chessboard[i][j+2]==1&&chessboard[i][j+3]==2) comresults[i][j]+=11;
                 if(chessboard[i-2][j-2]==0&&chessboard[i-1][j-1]==1&&chessboard[i+1][j+1]==1&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==2) comresults[i][j]+=11;
                 if(chessboard[i-2][j]==0&&chessboard[i-1][j]==1&&chessboard[i+1][j]==1&&chessboard[i+2][j]==1&&chessboard[i+3][j]==2) comresults[i][j]+=11;
                 if(chessboard[i-2][j+2]==0&&chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==2) comresults[i][j]+=11;

                 if(chessboard[i][j+2]==0&&chessboard[i][j+1]==2&&chessboard[i][j-1]==2&&chessboard[i][j-2]==2&&chessboard[i][j-3]==1) humresults[i][j]+=11;
                 if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==2&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==1) humresults[i][j]+=11;
                 if(chessboard[i+2][j]==0&&chessboard[i+1][j]==2&&chessboard[i-1][j]==2&&chessboard[i-2][j]==2&&chessboard[i-3][j]==1) humresults[i][j]+=11;
                 if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==2&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==1) humresults[i][j]+=11;
                 if(chessboard[i][j-2]==0&&chessboard[i][j-1]==2&&chessboard[i][j+1]==2&&chessboard[i][j+2]==2&&chessboard[i][j+3]==1) humresults[i][j]+=11;
                 if(chessboard[i-2][j-2]==0&&chessboard[i-1][j-1]==2&&chessboard[i+1][j+1]==2&&chessboard[i+2][j+2]==2&&chessboard[i+3][j+3]==1) humresults[i][j]+=11;
                 if(chessboard[i-2][j]==0&&chessboard[i-1][j]==2&&chessboard[i+1][j]==2&&chessboard[i+2][j]==2&&chessboard[i+3][j]==1) humresults[i][j]+=11;
                 if(chessboard[i-2][j+2]==0&&chessboard[i-1][j+1]==2&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==1) humresults[i][j]+=11;

                 //the 5th situation  *o@oox

                 if(chessboard[i][j+2]==2&&chessboard[i][j+1]==1&&chessboard[i][j-1]==1&&chessboard[i][j-2]==1&&chessboard[i][j-3]==0) comresults[i][j]+=11;
                 if(chessboard[i+2][j+2]==2&&chessboard[i+1][j+1]==1&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==0) comresults[i][j]+=11;
                 if(chessboard[i+2][j]==2&&chessboard[i+1][j]==1&&chessboard[i-1][j]==1&&chessboard[i-2][j]==1&&chessboard[i-3][j]==0) comresults[i][j]+=11;
                 if(chessboard[i+2][j-2]==2&&chessboard[i+1][j-1]==1&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==0) comresults[i][j]+=11;
                 if(chessboard[i][j-2]==2&&chessboard[i][j-1]==1&&chessboard[i][j+1]==1&&chessboard[i][j+2]==1&&chessboard[i][j+3]==0) comresults[i][j]+=11;
                 if(chessboard[i-2][j-2]==2&&chessboard[i-1][j-1]==1&&chessboard[i+1][j+1]==1&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==0) comresults[i][j]+=11;
                 if(chessboard[i-2][j]==2&&chessboard[i-1][j]==1&&chessboard[i+1][j]==1&&chessboard[i+2][j]==1&&chessboard[i+3][j]==0) comresults[i][j]+=11;
                 if(chessboard[i-2][j+2]==2&&chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==0) comresults[i][j]+=11;

                 if(chessboard[i][j+2]==1&&chessboard[i][j+1]==2&&chessboard[i][j-1]==2&&chessboard[i][j-2]==2&&chessboard[i][j-3]==0) humresults[i][j]+=11;
                 if(chessboard[i+2][j+2]==1&&chessboard[i+1][j+1]==2&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==0) humresults[i][j]+=11;
                 if(chessboard[i+2][j]==1&&chessboard[i+1][j]==2&&chessboard[i-1][j]==2&&chessboard[i-2][j]==2&&chessboard[i-3][j]==0) humresults[i][j]+=11;
                 if(chessboard[i+2][j-2]==1&&chessboard[i+1][j-1]==2&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==0) humresults[i][j]+=11;
                 if(chessboard[i][j-2]==1&&chessboard[i][j-1]==2&&chessboard[i][j+1]==2&&chessboard[i][j+2]==2&&chessboard[i][j+3]==0) humresults[i][j]+=11;
                 if(chessboard[i-2][j-2]==1&&chessboard[i-1][j-1]==2&&chessboard[i+1][j+1]==2&&chessboard[i+2][j+2]==2&&chessboard[i+3][j+3]==0) humresults[i][j]+=11;
                 if(chessboard[i-2][j]==1&&chessboard[i-1][j]==2&&chessboard[i+1][j]==2&&chessboard[i+2][j]==2&&chessboard[i+3][j]==0) humresults[i][j]+=11;
                 if(chessboard[i-2][j+2]==1&&chessboard[i-1][j+1]==2&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==0) humresults[i][j]+=11;

                 //the 6th situation  *@ooox

                 if(chessboard[i][j+1]==2&&chessboard[i][j-1]==1&&chessboard[i][j-2]==1&&chessboard[i][j-3]==1&&chessboard[i][j-4]==0) comresults[i][j]+=11;
                 if(chessboard[i+1][j+1]==2&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==1&&chessboard[i-4][j-4]==0) comresults[i][j]+=11;
                 if(chessboard[i+1][j]==2&&chessboard[i-1][j]==1&&chessboard[i-2][j]==1&&chessboard[i-3][j]==1&&chessboard[i-4][j]==0) comresults[i][j]+=11;
                 if(chessboard[i+1][j-1]==2&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==1&&chessboard[i-4][j+4]==0) comresults[i][j]+=11;
                 if(chessboard[i][j-1]==2&&chessboard[i][j+1]==1&&chessboard[i][j+2]==1&&chessboard[i][j+3]==1&&chessboard[i][j+4]==0) comresults[i][j]+=11;
                 if(chessboard[i-1][j-1]==2&&chessboard[i+1][j+1]==1&&chessboard[i+1][j+2]==1&&chessboard[i+3][j+3]==1&&chessboard[i+4][j+4]==0) comresults[i][j]+=11;
                 if(chessboard[i-1][j]==2&&chessboard[i+1][j]==1&&chessboard[i+2][j]==1&&chessboard[i+3][j]==1&&chessboard[i+4][j]==0) comresults[i][j]+=11;
                 if(chessboard[i-1][j+1]==2&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==1&&chessboard[i+4][j-4]==0) comresults[i][j]+=11;

                 if(chessboard[i][j+1]==1&&chessboard[i][j-1]==2&&chessboard[i][j-2]==2&&chessboard[i][j-3]==2&&chessboard[i][j-4]==0) humresults[i][j]+=11;
                 if(chessboard[i+1][j+1]==1&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==2&&chessboard[i-4][j-4]==0) humresults[i][j]+=11;
                 if(chessboard[i+1][j]==1&&chessboard[i-1][j]==2&&chessboard[i-2][j]==2&&chessboard[i-3][j]==2&&chessboard[i-4][j]==0) humresults[i][j]+=11;
                 if(chessboard[i+1][j-1]==1&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==2&&chessboard[i-4][j+4]==0) humresults[i][j]+=11;
                 if(chessboard[i][j-1]==1&&chessboard[i][j+1]==2&&chessboard[i][j+2]==2&&chessboard[i][j+3]==2&&chessboard[i][j+4]==0) humresults[i][j]+=11;
                 if(chessboard[i-1][j-1]==1&&chessboard[i+1][j+1]==2&&chessboard[i+1][j+2]==2&&chessboard[i+3][j+3]==2&&chessboard[i+4][j+4]==0) humresults[i][j]+=11;
                 if(chessboard[i-1][j]==1&&chessboard[i+1][j]==2&&chessboard[i+2][j]==2&&chessboard[i+3][j]==2&&chessboard[i+4][j]==0) humresults[i][j]+=11;
                 if(chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==2&&chessboard[i+4][j-4]==0) humresults[i][j]+=11;

                 //the 7th situation  @xooo*

                 if(chessboard[i][j+1]==0&&chessboard[i][j+2]==1&&chessboard[i][j+3]==1&&chessboard[i][j+4]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==1&&chessboard[i+4][j+4]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j]==0&&chessboard[i+2][j]==1&&chessboard[i+3][j]==1&&chessboard[i+4][j]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==1&&chessboard[i+4][j-4]==1) comresults[i][j]+=9;
                 if(chessboard[i][j-1]==0&&chessboard[i][j-2]==1&&chessboard[i][j-3]==1&&chessboard[i][j-4]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==1&&chessboard[i-4][j-4]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j]==0&&chessboard[i-2][j]==1&&chessboard[i-3][j]==1&&chessboard[i-4][j]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==1&&chessboard[i-4][j+4]==1) comresults[i][j]+=9;

                 if(chessboard[i][j+1]==0&&chessboard[i][j+2]==2&&chessboard[i][j+3]==2&&chessboard[i][j+4]==2) humresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==2&&chessboard[i+3][j+3]==2&&chessboard[i+4][j+4]==2) humresults[i][j]+=9;
                 if(chessboard[i+1][j]==0&&chessboard[i+2][j]==2&&chessboard[i+3][j]==2&&chessboard[i+4][j]==2) humresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==2&&chessboard[i+4][j-4]==2) humresults[i][j]+=9;
                 if(chessboard[i][j-1]==0&&chessboard[i][j-2]==2&&chessboard[i][j-3]==2&&chessboard[i][j-4]==2) humresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==2&&chessboard[i-4][j-4]==2) humresults[i][j]+=9;
                 if(chessboard[i-1][j]==0&&chessboard[i-2][j]==2&&chessboard[i-3][j]==2&&chessboard[i-4][j]==2) humresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==2&&chessboard[i-4][j+4]==2) humresults[i][j]+=9;

                 //the 8th situation  ox@oo*

                 if(chessboard[i][j+3]==2&&chessboard[i][j+2]==1&&chessboard[i][j+1]==1&&chessboard[i][j-1]==0&&chessboard[i][j-2]==1) comresults[i][j]+=9;
                 if(chessboard[i+3][j+3]==2&&chessboard[i+2][j+2]==1&&chessboard[i+1][j+1]==1&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==1) comresults[i][j]+=9;
                 if(chessboard[i+3][j]==2&&chessboard[i+2][j]==1&&chessboard[i+1][j]==1&&chessboard[i-1][j]==0&&chessboard[i-2][j]==1) comresults[i][j]+=9;
                 if(chessboard[i+3][j-3]==2&&chessboard[i+2][j-2]==1&&chessboard[i+1][j-1]==1&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==1) comresults[i][j]+=9;
                 if(chessboard[i][j-3]==2&&chessboard[i][j-2]==1&&chessboard[i][j-1]==1&&chessboard[i][j+1]==0&&chessboard[i][j+2]==1) comresults[i][j]+=9;
                 if(chessboard[i-3][j-3]==2&&chessboard[i-2][j-2]==1&&chessboard[i-1][j-1]==1&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==12) comresults[i][j]+=9;
                 if(chessboard[i-3][j]==2&&chessboard[i-2][j]==1&&chessboard[i-1][j]==1&&chessboard[i+1][j]==0&&chessboard[i+2][j]==1) comresults[i][j]+=9;
                 if(chessboard[i-3][j+3]==2&&chessboard[i-2][j+2]==1&&chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==1) comresults[i][j]+=9;

                 if(chessboard[i][j+3]==1&&chessboard[i][j+2]==2&&chessboard[i][j+1]==2&&chessboard[i][j-1]==0&&chessboard[i][j-2]==2) humresults[i][j]+=9;
                 if(chessboard[i+3][j+3]==1&&chessboard[i+2][j+2]==2&&chessboard[i+1][j+1]==2&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==2) humresults[i][j]+=9;
                 if(chessboard[i+3][j]==1&&chessboard[i+2][j]==2&&chessboard[i+1][j]==2&&chessboard[i-1][j]==0&&chessboard[i-2][j]==2) humresults[i][j]+=9;
                 if(chessboard[i+3][j-3]==1&&chessboard[i+2][j-2]==2&&chessboard[i+1][j-1]==2&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==2) humresults[i][j]+=9;
                 if(chessboard[i][j-3]==1&&chessboard[i][j-2]==2&&chessboard[i][j-1]==2&&chessboard[i][j+1]==0&&chessboard[i][j+2]==2) humresults[i][j]+=9;
                 if(chessboard[i-3][j-3]==1&&chessboard[i-2][j-2]==2&&chessboard[i-1][j-1]==2&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==2) humresults[i][j]+=9;
                 if(chessboard[i-3][j]==1&&chessboard[i-2][j]==2&&chessboard[i-1][j]==2&&chessboard[i+1][j]==0&&chessboard[i+2][j]==2) humresults[i][j]+=9;
                 if(chessboard[i-3][j+3]==1&&chessboard[i-2][j+2]==2&&chessboard[i-1][j+1]==2&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==2) humresults[i][j]+=9;

                 //the 9th situation   oxo@o*

                 if(chessboard[i][j+2]==2&&chessboard[i][j+1]==1&&chessboard[i][j-1]==1&&chessboard[i][j-2]==0&&chessboard[i][j-3]==1) comresults[i][j]+=9;
                 if(chessboard[i+2][j+2]==2&&chessboard[i+1][j+1]==1&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==1) comresults[i][j]+=9;
                 if(chessboard[i+2][j]==2&&chessboard[i+1][j]==1&&chessboard[i-1][j]==1&&chessboard[i-2][j]==0&&chessboard[i-3][j]==1) comresults[i][j]+=9;
                 if(chessboard[i+2][j-2]==2&&chessboard[i+1][j-1]==1&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==1) comresults[i][j]+=9;
                 if(chessboard[i][j-2]==2&&chessboard[i][j-1]==1&&chessboard[i][j+1]==1&&chessboard[i][j+2]==0&&chessboard[i][j+3]==1) comresults[i][j]+=9;
                 if(chessboard[i-2][j-2]==2&&chessboard[i-1][j-1]==1&&chessboard[i+1][j+1]==1&&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==1) comresults[i][j]+=9;
                 if(chessboard[i-2][j]==2&&chessboard[i-1][j]==1&&chessboard[i+1][j]==1&&chessboard[i+2][j]==0&&chessboard[i+3][j]==1) comresults[i][j]+=9;
                 if(chessboard[i-2][j+2]==2&&chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==1) comresults[i][j]+=9;

                 if(chessboard[i][j+2]==2&&chessboard[i][j+1]==2&&chessboard[i][j-1]==2&&chessboard[i][j-2]==0&&chessboard[i][j-3]==2) humresults[i][j]+=9;
                 if(chessboard[i+2][j+2]==2&&chessboard[i+1][j+1]==2&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==2) humresults[i][j]+=9;
                 if(chessboard[i+2][j]==2&&chessboard[i+1][j]==2&&chessboard[i-1][j]==2&&chessboard[i-2][j]==0&&chessboard[i-3][j]==2) humresults[i][j]+=9;
                 if(chessboard[i+2][j-2]==2&&chessboard[i+1][j-1]==2&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==2) humresults[i][j]+=9;
                 if(chessboard[i][j-2]==2&&chessboard[i][j-1]==2&&chessboard[i][j+1]==2&&chessboard[i][j+2]==0&&chessboard[i][j+3]==2) humresults[i][j]+=9;
                 if(chessboard[i-2][j-2]==2&&chessboard[i-1][j-1]==2&&chessboard[i+1][j+1]==2&&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==2) humresults[i][j]+=9;
                 if(chessboard[i-2][j]==2&&chessboard[i-1][j]==2&&chessboard[i+1][j]==2&&chessboard[i+2][j]==0&&chessboard[i+3][j]==2) humresults[i][j]+=9;
                 if(chessboard[i-2][j+2]==2&&chessboard[i-1][j+1]==2&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==2) humresults[i][j]+=9;

                 //the 10th situation   oxoo@*

                 if(chessboard[i][j+1]==2&&chessboard[i][j-1]==1&&chessboard[i][j-2]==1&&chessboard[i][j-3]==0&&chessboard[i][j-4]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==2&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==0&&chessboard[i-4][j-4]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j]==2&&chessboard[i-1][j]==1&&chessboard[i-2][j]==1&&chessboard[i-3][j]==0&&chessboard[i-4][j]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==2&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==0&&chessboard[i-4][j+4]==1) comresults[i][j]+=9;
                 if(chessboard[i][j-1]==2&&chessboard[i][j+1]==1&&chessboard[i][j+2]==1&&chessboard[i][j+3]==0&&chessboard[i][j+4]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==2&&chessboard[i+1][j+1]==1&&chessboard[i+1][j+2]==1&&chessboard[i+3][j+3]==0&&chessboard[i+4][j+4]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j]==2&&chessboard[i+1][j]==1&&chessboard[i+2][j]==1&&chessboard[i+3][j]==0&&chessboard[i+4][j]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==2&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==0&&chessboard[i+4][j-4]==1) comresults[i][j]+=9;

                 if(chessboard[i][j+1]==1&&chessboard[i][j-1]==2&&chessboard[i][j-2]==2&&chessboard[i][j-3]==0&&chessboard[i][j-4]==2) humresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==1&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==0&&chessboard[i-4][j-4]==2) humresults[i][j]+=9;
                 if(chessboard[i+1][j]==1&&chessboard[i-1][j]==2&&chessboard[i-2][j]==2&&chessboard[i-3][j]==0&&chessboard[i-4][j]==2) humresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==1&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==0&&chessboard[i-4][j+4]==2) humresults[i][j]+=9;
                 if(chessboard[i][j-1]==1&&chessboard[i][j+1]==2&&chessboard[i][j+2]==2&&chessboard[i][j+3]==0&&chessboard[i][j+4]==2) humresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==1&&chessboard[i+1][j+1]==2&&chessboard[i+1][j+2]==2&&chessboard[i+3][j+3]==0&&chessboard[i+4][j+4]==2) humresults[i][j]+=9;
                 if(chessboard[i-1][j]==1&&chessboard[i+1][j]==2&&chessboard[i+2][j]==2&&chessboard[i+3][j]==0&&chessboard[i+4][j]==2) humresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==0&&chessboard[i+4][j-4]==2) humresults[i][j]+=9;

                 //the 11th situation   @oxoo

                 if(chessboard[i][j+1]==1&&chessboard[i][j+2]==0&&chessboard[i][j+3]==1&&chessboard[i][j+4]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==1&&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==1&&chessboard[i+4][j+4]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j]==1&&chessboard[i+2][j]==0&&chessboard[i+3][j]==1&&chessboard[i+4][j]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==1&&chessboard[i+4][j-4]==1) comresults[i][j]+=9;
                 if(chessboard[i][j-1]==1&&chessboard[i][j-2]==0&&chessboard[i][j-3]==1&&chessboard[i][j-4]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==1&&chessboard[i-4][j-4]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j]==1&&chessboard[i-2][j]==0&&chessboard[i-3][j]==1&&chessboard[i-4][j]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==1&&chessboard[i-4][j+4]==1) comresults[i][j]+=9;

                 if(chessboard[i][j+1]==2&&chessboard[i][j+2]==0&&chessboard[i][j+3]==2&&chessboard[i][j+4]==2) humresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==2&&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==2&&chessboard[i+4][j+4]==2) humresults[i][j]+=9;
                 if(chessboard[i+1][j]==2&&chessboard[i+2][j]==0&&chessboard[i+3][j]==2&&chessboard[i+4][j]==2) humresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==2&&chessboard[i+4][j-4]==2) humresults[i][j]+=9;
                 if(chessboard[i][j-1]==2&&chessboard[i][j-2]==0&&chessboard[i][j-3]==2&&chessboard[i][j-4]==2) humresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==2&&chessboard[i-4][j-4]==2) humresults[i][j]+=9;
                 if(chessboard[i-1][j]==2&&chessboard[i-2][j]==0&&chessboard[i-3][j]==2&&chessboard[i-4][j]==2) humresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==2&&chessboard[i-4][j+4]==2) humresults[i][j]+=9;

                 //the 12th situation   o@xoo

                 if(chessboard[i][j-1]==1&&chessboard[i][j+1]==0&&chessboard[i][j+2]==0&&chessboard[i][j+3]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==1&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j]==1&&chessboard[i+1][j]==0&&chessboard[i+2][j]==0&&chessboard[i+3][j]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==1) comresults[i][j]+=9;
                 if(chessboard[i][j+1]==1&&chessboard[i][j-1]==0&&chessboard[i][j-2]==0&&chessboard[i][j-3]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==1&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j]==1&&chessboard[i-1][j]==0&&chessboard[i-2][j]==0&&chessboard[i-3][j]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==1&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==1) comresults[i][j]+=9;

                 if(chessboard[i][j-1]==2&&chessboard[i][j+1]==0&&chessboard[i][j+2]==0&&chessboard[i][j+3]==1) humresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==2&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==1) humresults[i][j]+=9;
                 if(chessboard[i-1][j]==2&&chessboard[i+1][j]==0&&chessboard[i+2][j]==0&&chessboard[i+3][j]==1) humresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==2&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==1) humresults[i][j]+=9;
                 if(chessboard[i][j+1]==2&&chessboard[i][j-1]==0&&chessboard[i][j-2]==0&&chessboard[i][j-3]==1) humresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==2&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==1) humresults[i][j]+=9;
                 if(chessboard[i+1][j]==2&&chessboard[i-1][j]==0&&chessboard[i-2][j]==0&&chessboard[i-3][j]==1) humresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==2&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==1) humresults[i][j]+=9;


     }
}


void Gobang::r_three(){

     for(int i=1;i<14;i++)
         for(int j=1;j<14;j++){

                 if(chessboard[i][j]!=0) continue;

                 //the first situation    x@oox

                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==1&&chessboard[i][j+2]==1&&chessboard[i][j+3]==0) comresults[i][j]+=10;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==1&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==0) comresults[i][j]+=10;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==1&&chessboard[i+2][j]==1&&chessboard[i+3][j]==0) comresults[i][j]+=10;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==0) comresults[i][j]+=10;
                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==1&&chessboard[i][j-2]==1&&chessboard[i][j-3]==0) comresults[i][j]+=10;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==0) comresults[i][j]+=10;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==1&&chessboard[i-2][j]==1&&chessboard[i-3][j]==0) comresults[i][j]+=10;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==0) comresults[i][j]+=10;

                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==2&&chessboard[i][j+2]==2&&chessboard[i][j+3]==0) humresults[i][j]+=10;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==2&&chessboard[i+2][j+2]==2&&chessboard[i+3][j+3]==0) humresults[i][j]+=10;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==2&&chessboard[i+2][j]==2&&chessboard[i+3][j]==0) humresults[i][j]+=10;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==0) humresults[i][j]+=10;
                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==2&&chessboard[i][j-2]==2&&chessboard[i][j-3]==0) humresults[i][j]+=10;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==0) humresults[i][j]+=10;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==2&&chessboard[i-2][j]==2&&chessboard[i-3][j]==0) humresults[i][j]+=10;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==0) humresults[i][j]+=10;


                 //the second situation   xo@ox
                 if(chessboard[i][j+1]==1&&chessboard[i][j-1]==1&&chessboard[i][j-2]==0&&chessboard[i][j+2]==0) comresults[i][j]+=10;
                 if(chessboard[i-1][j]==1&&chessboard[i+1][j]==1&&chessboard[i-2][j]==0&&chessboard[i+2][j]==0) comresults[i][j]+=10;
                 if(chessboard[i+1][j+1]==1&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==0&&chessboard[i+2][j+2]==0) comresults[i][j]+=10;
                 if(chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==0&&chessboard[i+2][j-2]==0) comresults[i][j]+=10;

                 if(chessboard[i][j+1]==2&&chessboard[i][j-1]==2&&chessboard[i][j-2]==0&&chessboard[i][j+2]==0) humresults[i][j]+=10;
                 if(chessboard[i-1][j]==2&&chessboard[i+1][j]==2&&chessboard[i-2][j]==0&&chessboard[i+2][j]==0) humresults[i][j]+=10;
                 if(chessboard[i+1][j+1]==2&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==0&&chessboard[i+2][j+2]==0) humresults[i][j]+=10;
                 if(chessboard[i-1][j+1]==2&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==0&&chessboard[i+2][j-2]==0) humresults[i][j]+=10;

                 //the third situation x@xoox

                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==0&&chessboard[i][j+2]==1&&chessboard[i][j+3]==1&&chessboard[i][j+4]==0) comresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==1&&chessboard[i+4][j+4]==0) comresults[i][j]+=9;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==0&&chessboard[i+2][j]==1&&chessboard[i+3][j]==1&&chessboard[i+4][j]==0) comresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==1&&chessboard[i+4][j-4]==0) comresults[i][j]+=9;
                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==0&&chessboard[i][j-2]==1&&chessboard[i][j-3]==1&&chessboard[i][j-4]==0) comresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==1&&chessboard[i-4][j-4]==0) comresults[i][j]+=9;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==0&&chessboard[i-2][j]==1&&chessboard[i-3][j]==1&&chessboard[i-4][j]==0) comresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==1&&chessboard[i-4][j+4]==0) comresults[i][j]+=9;

                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==0&&chessboard[i][j+2]==2&&chessboard[i][j+3]==2&&chessboard[i][j+4]==0) humresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==2&&chessboard[i+3][j+3]==2&&chessboard[i+4][j+4]==0) humresults[i][j]+=9;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==0&&chessboard[i+2][j]==2&&chessboard[i+3][j]==2&&chessboard[i+4][j]==0) humresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==2&&chessboard[i+4][j-4]==0) humresults[i][j]+=9;
                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==0&&chessboard[i][j-2]==2&&chessboard[i][j-3]==2&&chessboard[i][j-4]==0) humresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==2&&chessboard[i-4][j-4]==0) humresults[i][j]+=9;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==0&&chessboard[i-2][j]==2&&chessboard[i-3][j]==2&&chessboard[i-4][j]==0) humresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==2&&chessboard[i-4][j+4]==0) humresults[i][j]+=9;

                 //the fourth situation   xox@ox

                 if(chessboard[i][j+2]==0&&chessboard[i][j+1]==1&&chessboard[i][j-1]==0&&chessboard[i][j-2]==1&&chessboard[i][j-3]==0) comresults[i][j]+=9;
                 if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==1&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==0) comresults[i][j]+=9;
                 if(chessboard[i+2][j]==0&&chessboard[i+1][j]==1&&chessboard[i-1][j]==0&&chessboard[i-2][j]==1&&chessboard[i-3][j]==0) comresults[i][j]+=9;
                 if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==1&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==0) comresults[i][j]+=9;
                 if(chessboard[i][j-2]==0&&chessboard[i][j-1]==1&&chessboard[i][j+1]==0&&chessboard[i][j+2]==1&&chessboard[i][j+3]==0) comresults[i][j]+=9;
                 if(chessboard[i-2][j-2]==0&&chessboard[i-1][j-1]==1&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==0) comresults[i][j]+=9;
                 if(chessboard[i-2][j]==0&&chessboard[i-1][j]==1&&chessboard[i+1][j]==0&&chessboard[i+2][j]==1&&chessboard[i+3][j]==0) comresults[i][j]+=9;
                 if(chessboard[i-2][j+2]==0&&chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==0) comresults[i][j]+=9;

                 if(chessboard[i][j+2]==0&&chessboard[i][j+1]==2&&chessboard[i][j-1]==0&&chessboard[i][j-2]==2&&chessboard[i][j-3]==0) humresults[i][j]+=9;
                 if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==2&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==0) humresults[i][j]+=9;
                 if(chessboard[i+2][j]==0&&chessboard[i+1][j]==2&&chessboard[i-1][j]==0&&chessboard[i-2][j]==2&&chessboard[i-3][j]==0) humresults[i][j]+=9;
                 if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==2&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==0) humresults[i][j]+=9;
                 if(chessboard[i][j-2]==0&&chessboard[i][j-1]==2&&chessboard[i][j+1]==0&&chessboard[i][j+2]==2&&chessboard[i][j+3]==0) humresults[i][j]+=9;
                 if(chessboard[i-2][j-2]==0&&chessboard[i-1][j-1]==2&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==2&&chessboard[i+3][j+3]==0) humresults[i][j]+=9;
                 if(chessboard[i-2][j]==0&&chessboard[i-1][j]==2&&chessboard[i+1][j]==0&&chessboard[i+2][j]==2&&chessboard[i+3][j]==0) humresults[i][j]+=9;
                 if(chessboard[i-2][j+2]==0&&chessboard[i-1][j+1]==2&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==0) humresults[i][j]+=9;

                 //the fifth situation    xoxo@x

                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==1&&chessboard[i][j-2]==0&&chessboard[i][j-3]==1&&chessboard[i][j-4]==0) comresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==1&&chessboard[i-4][j-4]==0) comresults[i][j]+=9;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==1&&chessboard[i-2][j]==0&&chessboard[i-3][j]==1&&chessboard[i-4][j]==0) comresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==1&&chessboard[i-4][j+4]==0) comresults[i][j]+=9;
                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==1&&chessboard[i][j+2]==0&&chessboard[i][j+3]==1&&chessboard[i][j+4]==0) comresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==1&&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==1&&chessboard[i+4][j+4]==0) comresults[i][j]+=9;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==1&&chessboard[i+2][j]==0&&chessboard[i+3][j]==1&&chessboard[i+4][j]==0) comresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==1&&chessboard[i+4][j-4]==0) comresults[i][j]+=9;

                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==2&&chessboard[i][j-2]==0&&chessboard[i][j-3]==2&&chessboard[i][j-4]==0) humresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==2&&chessboard[i-4][j-4]==0) humresults[i][j]+=9;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==2&&chessboard[i-2][j]==0&&chessboard[i-3][j]==2&&chessboard[i-4][j]==0) humresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==2&&chessboard[i-4][j+4]==0) humresults[i][j]+=9;
                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==2&&chessboard[i][j+2]==0&&chessboard[i][j+3]==2&&chessboard[i][j+4]==0) humresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==2&&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==2&&chessboard[i+4][j+4]==0) humresults[i][j]+=9;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==2&&chessboard[i+2][j]==0&&chessboard[i+3][j]==2&&chessboard[i+4][j]==0) humresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==2&&chessboard[i+4][j-4]==0) humresults[i][j]+=9;

                 //the sixth situation    x@xoxox

                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==0&&chessboard[i][j+2]==1&&chessboard[i][j+3]==0&&chessboard[i][j+4]==1&&chessboard[i][j+5]==0) comresults[i][j]+=8;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==0&&chessboard[i+4][j+4]==1&&chessboard[i+5][j+5]==0) comresults[i][j]+=8;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==0&&chessboard[i+2][j]==1&&chessboard[i+3][j]==0&&chessboard[i+4][j]==1&&chessboard[i+5][j]==0) comresults[i][j]+=8;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==0&&chessboard[i+4][j-4]==1&&chessboard[i+5][j-5]==0) comresults[i][j]+=8;
                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==0&&chessboard[i][j-2]==1&&chessboard[i][j-3]==0&&chessboard[i][j-4]==1&&chessboard[i][j-5]==0) comresults[i][j]+=8;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==0&&chessboard[i-4][j-4]==1&&chessboard[i-5][j-5]==0) comresults[i][j]+=8;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==0&&chessboard[i-2][j]==1&&chessboard[i-3][j]==0&&chessboard[i-4][j]==1&&chessboard[i-5][j]==0) comresults[i][j]+=8;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==0&&chessboard[i-4][j+4]==1&&chessboard[i-5][j+5]==0) comresults[i][j]+=8;

                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==0&&chessboard[i][j+2]==2&&chessboard[i][j+3]==0&&chessboard[i][j+4]==2&&chessboard[i][j+5]==0) humresults[i][j]+=8;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==2&&chessboard[i+3][j+3]==0&&chessboard[i+4][j+4]==2&&chessboard[i+5][j+5]==0) humresults[i][j]+=8;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==0&&chessboard[i+2][j]==2&&chessboard[i+3][j]==0&&chessboard[i+4][j]==2&&chessboard[i+5][j]==0) humresults[i][j]+=8;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==0&&chessboard[i+4][j-4]==2&&chessboard[i+5][j-5]==0) humresults[i][j]+=8;
                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==0&&chessboard[i][j-2]==2&&chessboard[i][j-3]==0&&chessboard[i][j-4]==2&&chessboard[i][j-5]==0) humresults[i][j]+=8;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==0&&chessboard[i-4][j-4]==2&&chessboard[i-5][j-5]==0) humresults[i][j]+=8;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==0&&chessboard[i-2][j]==2&&chessboard[i-3][j]==0&&chessboard[i-4][j]==2&&chessboard[i-5][j]==0) humresults[i][j]+=8;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==0&&chessboard[i-4][j+4]==2&&chessboard[i-5][j+5]==0) humresults[i][j]+=8;


                 }

}



void Gobang::r_two(){


     for(int i=1;i<14;i++)
            for(int j=1;j<14;j++){

                    if(chessboard[i][j]!=0) continue;

                    //the first situation xx@oxx

                    if(chessboard[i][j-2]==0&&chessboard[i][j-1]==0&&chessboard[i][j+1]==1&&chessboard[i][j+2]==0&&chessboard[i][j+3]==0) comresults[i][j]+=2;
                    if(chessboard[i-2][j-2]==0&&chessboard[i-2][j-1]==0&&chessboard[i+1][j+1]==1&&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==0) comresults[i][j]+=2;
                    if(chessboard[i-2][j]==0&&chessboard[i-1][j]==0&&chessboard[i+1][j]==1&&chessboard[i+2][j]==0&&chessboard[i+3][j]==0) comresults[i][j]+=2;
                    if(chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==0&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==0) comresults[i][j]+=2;
                    if(chessboard[i][j+2]==0&&chessboard[i][j+1]==0&&chessboard[i][j-1]==1&&chessboard[i][j-2]==0&&chessboard[i][j-3]==0) comresults[i][j]+=2;
                    if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==0) comresults[i][j]+=2;
                    if(chessboard[i+2][j]==0&&chessboard[i+1][j]==0&&chessboard[i-1][j]==1&&chessboard[i-2][j]==0&&chessboard[i-3][j]==0) comresults[i][j]+=2;
                    if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==0) comresults[i][j]+=2;

                    if(chessboard[i][j-2]==0&&chessboard[i][j-1]==0&&chessboard[i][j+1]==2&&chessboard[i][j+2]==0&&chessboard[i][j+3]==0) humresults[i][j]+=2;
                    if(chessboard[i-2][j-2]==0&&chessboard[i-2][j-1]==0&&chessboard[i+1][j+1]==2&&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==0) humresults[i][j]+=2;
                    if(chessboard[i-2][j]==0&&chessboard[i-1][j]==0&&chessboard[i+1][j]==2&&chessboard[i+2][j]==0&&chessboard[i+3][j]==0) humresults[i][j]+=2;
                    if(chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==0&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==0) humresults[i][j]+=2;
                    if(chessboard[i][j+2]==0&&chessboard[i][j+1]==0&&chessboard[i][j-1]==2&&chessboard[i][j-2]==0&&chessboard[i][j-3]==0) humresults[i][j]+=2;
                    if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==0) humresults[i][j]+=2;
                    if(chessboard[i+2][j]==0&&chessboard[i+1][j]==0&&chessboard[i-1][j]==2&&chessboard[i-2][j]==0&&chessboard[i-3][j]==0) humresults[i][j]+=2;
                    if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==0) humresults[i][j]+=2;

                    //the second situation   xx@xox

                    if(chessboard[i][j-2]==0&&chessboard[i][j-1]==0&&chessboard[i][j+1]==0&&chessboard[i][j+2]==1&&chessboard[i][j+3]==0) comresults[i][j]+=1;
                    if(chessboard[i-2][j-2]==0&&chessboard[i-2][j-1]==0&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==0) comresults[i][j]+=1;
                    if(chessboard[i-2][j]==0&&chessboard[i-1][j]==0&&chessboard[i+1][j]==0&&chessboard[i+2][j]==1&&chessboard[i+3][j]==0) comresults[i][j]+=1;
                    if(chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==0&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==0) comresults[i][j]+=1;
                    if(chessboard[i][j+2]==0&&chessboard[i][j+1]==0&&chessboard[i][j-1]==0&&chessboard[i][j-2]==1&&chessboard[i][j-3]==0) comresults[i][j]+=1;
                    if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==0) comresults[i][j]+=1;
                    if(chessboard[i+2][j]==0&&chessboard[i+1][j]==0&&chessboard[i-1][j]==0&&chessboard[i-2][j]==1&&chessboard[i-3][j]==0) comresults[i][j]+=1;
                    if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==0) comresults[i][j]+=1;

                    if(chessboard[i][j-2]==0&&chessboard[i][j-1]==0&&chessboard[i][j+1]==0&&chessboard[i][j+2]==1&&chessboard[i][j+3]==0) humresults[i][j]+=1;
                    if(chessboard[i-2][j-2]==0&&chessboard[i-2][j-1]==0&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==0) humresults[i][j]+=1;
                    if(chessboard[i-2][j]==0&&chessboard[i-1][j]==0&&chessboard[i+1][j]==0&&chessboard[i+2][j]==1&&chessboard[i+3][j]==0) humresults[i][j]+=1;
                    if(chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==0&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==0) humresults[i][j]+=1;
                    if(chessboard[i][j+2]==0&&chessboard[i][j+1]==0&&chessboard[i][j-1]==0&&chessboard[i][j-2]==1&&chessboard[i][j-3]==0) humresults[i][j]+=1;
                    if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==0) humresults[i][j]+=1;
                    if(chessboard[i+2][j]==0&&chessboard[i+1][j]==0&&chessboard[i-1][j]==0&&chessboard[i-2][j]==1&&chessboard[i-3][j]==0) humresults[i][j]+=1;
                    if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==0) humresults[i][j]+=1;


                    }
}




//Start game


void go(int n){
     Gobang g;
     if(n==1)
     {
             cout<<"Choose who be the First:"<<endl;
             cout<<"     1.Player First"<<endl;
             cout<<"     2.Computer First"<<endl;
             int n;
             cin>>n;
             if(n==2)  g.firstgo();
     while(1){
              if(g.ifwin()==1) {
                                g.print(1);
                                cout<<"Computer Win！"<<endl;
                              break;
                              }
              if(g.ifwin()==2){
                              g.print(1);
                              cout<<"Player Win！"<<endl;
                              break;
                              }
              g.print(1);
              g.input(1);
              if(g.returngoback()==1) {cout<<"surrender!"<<endl;return;}
              if(g.ifwin()==1) {
                                g.print(1);
                              cout<<"Computer Win!"<<endl;
                              break;
                              }
              if(g.ifwin()==2){
                              g.print(1);
                              cout<<"Player Win!"<<endl;
                              break;
                              }
              g.think();
              }
     }
     if(n==2){
              while(1){
              if(g.ifwin()==1) {
                                g.print(2);
                              cout<<"Player1 Win!"<<endl;
                              break;
                              }
              if(g.ifwin()==2){
                              g.print(2);
                              cout<<"Player2 Win!"<<endl;
                              break;
                              }
              g.print(2);
              g.input(2);
              if(g.returngoback()==1) {cout<<"surrender!"<<endl;return;}
              }
              }


}




void explain(){
     cout<<"****************instruction****************"<<endl;

     cout<<"how to play: "<<endl;
     cout<<"   on the chessboard, * represents computer's(or the second player's) stone, o represents player's."<<endl;
     cout<<"   first enter the row you want to put your stone. Then enter the column. you can use space to separate.(don't enter other things not numbers.)"<<endl;
     cout<<"   you can enter 222 to surrender!"<<endl;
     cout<<"   at the bottom of chessboard, you can see the last step from computer or another player."<<endl;
     }



//main function

int main(){
    while(1){
            Gobang m;

             //system("cls");
             cout<<"****************Gobang****************"<<endl;
             cout<<"                2015.4.20"<<endl;
             cout<<"Input the number to choose:"<<endl;
             cout<<"             1.With computer."<<endl;
             cout<<"             2.With another player."<<endl;
             cout<<"             4.Instruction"<<endl;
             cout<<"             0.Quit"<<endl;

             int s;
             cin>>s;
             if(s==1) go(1);
             if(s==2) go(2);
             if(s==4) explain();
             if(s==0) exit(0);
             cout<<"Back to menu?  y: Yes  n: Quit game "<<endl;
             char yn;
             cin>>yn;
             if(yn=='n') break;
            }
}
