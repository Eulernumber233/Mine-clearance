#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#define L 16
#define W 16
#define B 40
void print(int x,int y,int n){
	settextcolor(BLACK);
	settextstyle(20,20,"¿¬Ìå");
	setbkmode(TRANSPARENT);
	setfillcolor(WHITE);
	setlinecolor(WHITE);
	fillrectangle(x*30+1,(y+2)*30+1,(x+1)*30-1,(y+3)*30-1);
	switch(n){
		case 1:	settextcolor(BLUE);
		        outtextxy(x*30+6,(y+2)*30+6,"1");break; 
		case 2: settextcolor(GREEN);
		    	outtextxy(x*30+6,(y+2)*30+6,"2");break; 
		case 3:	settextcolor(RED);
	        	outtextxy(x*30+6,(y+2)*30+6,"3");break; 
		case 4:	settextcolor(RGB(0,0,128));
		        outtextxy(x*30+6,(y+2)*30+6,"4");break; 
		case 5:	settextcolor(RGB(176,7,14));
		        outtextxy(x*30+6,(y+2)*30+6,"5");break; 
		case 6:	settextcolor(RGB(72,209,204));
		        outtextxy(x*30+6,(y+2)*30+6,"6");break; 
		case 7:	settextcolor(RED);
		        outtextxy(x*30+6,(y+2)*30+6,"7");break; 
		case 8:	settextcolor(BLACK);
		        outtextxy(x*30+6,(y+2)*30+6,"8");break; 
		case 10:setcolor(RED);
		        setfillcolor(RED);
	            fillcircle(x*30+15,(y+2)*30+15,10);
	            break; 
	    case 0: break;
		case -1:settextcolor(RED);
		          setfillcolor(RGB(129,129,129));
		        setlinecolor(RGB(129,129,129));
	            fillrectangle(x*30+1,(y+2)*30+1,(x+1)*30-1,(y+3)*30-1);	
		        outtextxy(x*30+6,(y+2)*30+6,"?");break;
		case -2:setfillcolor(RGB(129,129,129));
		        setlinecolor(RGB(129,129,129));
	            fillrectangle(x*30+1,(y+2)*30+1,(x+1)*30-1,(y+3)*30-1);	
				break;	 		      
	}

}
 
void turn(int x,int y,int A[][W],int JUD[][W]){
    JUD[x][y]=1;
	print(x,y,0);
	if(y+1<W&&A[x][y+1]!=10&&JUD[x][y+1]==0){
			if(A[x][y+1]==0){
				turn(x,y+1,A,JUD);
			    }
			print(x,y+1,A[x][y+1]);JUD[x][y+1]=1;	
		}
		
	   	if(y-1>=0&&A[x][y-1]!=10&&JUD[x][y-1]==0){
	   		if(A[x][y-1]==0){
	   			turn(x,y-1,A,JUD);
			    }
			print(x,y-1,A[x][y-1]);JUD[x][y-1]=1;	
		   }
		   
	   	if(x+1<L&&A[x+1][y]!=10&&JUD[x+1][y]==0){
	   		if(A[x+1][y]==0){
	   			turn(x+1,y,A,JUD);
			    }
			print(x+1,y,A[x+1][y]);JUD[x+1][y]=1;	
		   }
		   
	   	if(x-1>=0&&A[x-1][y]!=10&&JUD[x-1][y]==0){
	   		if(A[x-1][y]==0){
	   			turn(x-1,y,A,JUD);
			   }
			print(x-1,y,A[x-1][y]);JUD[x-1][y]=1;	
		   }
		   
		if(x-1>=0&&y-1>=0&&A[x-1][y-1]!=10&&JUD[x-1][y-1]==0){
			if(A[x-1][y-1]==0){
				turn(x-1,y-1,A,JUD);
			}
			print(x-1,y-1,A[x-1][y-1]);JUD[x-1][y-1]=1;	
		}
		
	   	if(y+1<W&&x-1>=0&&A[x-1][y+1]!=10&&JUD[x-1][y+1]==0){
	   		if(A[x-1][y+1]==0){
	   			turn(x-1,y+1,A,JUD);
			    }
			print(x-1,y+1,A[x-1][y+1]);JUD[x-1][y+1]=1;	
		   }
		   
	   	if(x+1<L&&y-1>=0&&A[x+1][y-1]!=10&&JUD[x+1][y-1]==0){
	   		if(A[x+1][y-1]==0){
	   			turn(x+1,y-1,A,JUD);
			   }
			print(x+1,y-1,A[x+1][y-1]);JUD[x+1][y-1]=1;	
		   }
		   
	   	if(x+1<L&&y+1<W&&A[x+1][y+1]!=10&&JUD[x+1][y+1]==0){
	   		if(A[x+1][y+1]==0){
	   			turn(x+1,y+1,A,JUD);
			   }
			print(x+1,y+1,A[x+1][y+1]);JUD[x+1][y+1]=1;	
		   }   	
}

int main(){
	
	initgraph(L*30+1,(W+2)*30+1,STREAM_SEEK_END);
	setbkcolor(RGB(129,129,129)); 
	cleardevice();
	
	int x=0,y=0;	
	int i,j;
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID,1);
	for(i=0;i<=L;i++){
		line(i*30,60,i*30,(W+2)*30);
	}
	for(i=2;i<=W+2;i++){
		line(1,30*i,L*30,30*i);
	}
		
	int A[L][W],JUD[L][W],qi[L][W];
	for(i=0;i<L;i++){
		for(j=0;j<W;j++){
			A[i][j]=0;
			JUD[i][j]=0;
			qi[i][j]=0;
		}
	}
	i=0;j=0;
	
	int n,N,B_[B],jud=1;
	srand(time(0));
	while(i<=B){
		j=i;
		N=rand();
		n=N%(W*L);
		for(j=0;j<i;j++){
			if(B_[j]==n){
				jud=0;
				break;
			}	
		}
		if(jud==1){
			B_[i]=n;
			i++;
		}
		jud=1;
	}
	jud=0;n=0;

	i=0;j=0;
A[0][0]=0;

    x=0;y=0;
    for(i=0;i<B;i++){
    	x=B_[i]%L;
    	y=B_[i]/L;
    	A[x][y]=10;
    	JUD[x][y]=1;
    	if(y+1<W&&A[x][y+1]<10)A[x][y+1]+=1;
    	if(y-1>=0&&A[x][y-1]<10)A[x][y-1]+=1;
    	if(x+1<L&&A[x+1][y]<10)A[x+1][y]+=1;
    	if(x-1>=0&&A[x-1][y]<10)A[x-1][y]+=1;
    	
    	if(x-1>=0&&y-1>=0&&A[x-1][y-1]<10)A[x-1][y-1]+=1;
    	if(y+1<W&&x-1>=0&&A[x-1][y+1]<10)A[x-1][y+1]+=1;
    	if(x+1<L&&y-1>=0&&A[x+1][y-1]<10)A[x+1][y-1]+=1;
    	if(x+1<L&&y+1<W&&A[x+1][y+1]<10)A[x+1][y+1]+=1;
	}
	x=0;y=0;

//Î»ÖÃ 
/*	for(i=0;i<W;i++){
		for(j=0;j<L;j++){
			printf("%d\t",A[j][i]);
		}printf("\n");
	}
	i=0;j=0;
*/
	
	int ctrl=1,sum=1;
	while(ctrl==1){
		if(MouseHit()){
			MOUSEMSG msg=GetMouseMsg();
			if(msg.y>60){
				switch(msg.uMsg){
					case WM_LBUTTONDOWN:
						x=msg.x/30;
			            y=(msg.y-60)/30;
			            if((JUD[x][y]==0||A[x][y]==10)&&qi[x][y]==0){
				            print(x,y,A[x][y]);
							if(A[x][y]==10){
								ctrl=2;
							}
							if(A[x][y]==0){
								turn(x,y,A,JUD);
							}
							if(A[x][y]!=0&&A[x][y]!=10){
								JUD[x][y]=1;
							}						
					    }
						break;
	    			case WM_RBUTTONDOWN:
						x=msg.x/30;
			            y=(msg.y-60)/30;
			            if(A[x][y]==10||JUD[x][y]==0){
			            	if(qi[x][y]==1){
			            		qi[x][y]=0;
			            		print(x,y,-2);
							}else
							{
								qi[x][y]=1;
								print(x,y,-1);
							}
						}
						break;	
				}
		    }		
		}
		for(i=0;i<L;i++){
			for(j=0;j<W;j++){
				sum*=JUD[i][j];
			}
		}
		if(sum==1){
			ctrl=0;
			break;
		}
		sum=1;
	}
	settextcolor(RED);
	settextstyle(30,0,"¿¬Ìå"); 
	setbkmode(TRANSPARENT);
	if(ctrl==2){
		outtextxy(20,20,"YOU FAULT!");
	}
	if(ctrl==0){
		outtextxy(20,20,"YOU WIN!");
	}
	
	getchar();
	closegraph();		
} 
