#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<time.h>

class Game
{
private:
	bool is_begin=false;// 是否开始计时
	int L,W,B;// 长度，宽度，雷数
	clock_t begin_time=-1,end_time=-1;
	int ctrl=1;// 判断是否结束，是输是赢
	int**A,**JUD,**qi;	// A:记录数字和地雷  JUD:记录是否被点击  qi：记录是否为标记？
public:
	Game();// 初始化
	~Game();	
	void print(int x,int y,int n); // 根据位置输出图像
	void turn(int x,int y,int**A,int**JUD);// 计算点击后要输出图像的位置
	void event_tick();// 获取鼠标信息
	void is_end();
	int get_ctrl()const {return ctrl;}
};

Game::Game()
{
	int mode=0;
	std::cout<<"请选择模式(1:高级 2:中级 3:低级 0:自定义):"<<std::endl;
	std::cin>>mode;
	switch(mode)
	{
		case 1:W=16;L=30;B=99;break;			
		case 2:W=16;L=16;B=40;break;
		case 3:W=9;L=9;B=10;break;
		default:
			do
			{
				std::cout<<"请输入长度"<<std::endl;
				std::cin>>L;
				std::cout<<"请输入宽度"<<std::endl;
				std::cin>>W;
				std::cout<<"请输入雷数"<<std::endl;
				std::cin>>B;
				if(L*W<=B)std::cout<<"雷数过多，请重新输入"<<std::endl;
			}while(L*W<=B);	break;
	}
		
	// 绘制初始画面
	initgraph(L*30+1,(W+2)*30+1);
	setbkcolor(RGB(129,129,129)); 
	cleardevice();
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID,1);
	for(int i=0;i<=L;i++){
		line(i*30,60,i*30,(W+2)*30);
	}
	for(int i=2;i<=W+2;i++){
		line(1,30*i,L*30,30*i);
	}

	A=(int**)malloc(sizeof(int*)*L);
	JUD=(int**)malloc(sizeof(int*)*L);
	qi=(int**)malloc(sizeof(int*)*L);	
	for(int i=0;i<L;i++)
	{
		A[i]=(int*)malloc(sizeof(int)*W);
		JUD[i]=(int*)malloc(sizeof(int)*W);
		qi[i]=(int*)malloc(sizeof(int)*W);
	}
	for(int i=0;i<L;i++)
	{
		for(int j=0;j<W;j++)
		{
			A[i][j]=0;
			JUD[i][j]=0;
			qi[i][j]=0;
		}
	}
	int B_[B];// 暂存地雷序号
	int jud=1;
	srand(time(0));	
	// 确定地雷序号
	for(int i=0;i<=B;)
	{
		int n=rand()%(W*L);
		for(int j=0;j<i;j++)
		{
			if(B_[j]==n)
			{					
				jud=0;
				break;
			}	
		}
		if(jud==1)
		{
			B_[i]=n;
			i++;
		}
		jud=1;
	}
	// 确定地雷位置，标定周围序号
    for(int i=0;i<B;i++)
	{
    	int x=B_[i]%L;
    	int y=B_[i]/L;
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
}

Game::~Game()
{
	settextcolor(RED);
	settextstyle(30,0,"楷体"); 
	setbkmode(TRANSPARENT);
	if(ctrl==2)
	{
		outtextxy(10,20,"FAULT!");
	}
	if(ctrl==0)
	{
		outtextxy(10,20,"WIN!");
	}

	std::cin.get();		
	getchar();
	closegraph();
}

void Game::print(int x,int y,int n)
{
	settextcolor(BLACK);
	settextstyle(20,20,"楷体");
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

void Game::turn(int x,int y,int**A,int**JUD)
{
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

void Game::event_tick()
{
	if(!MouseHit())return;
	if(end_time==-1&&is_begin==true)// 开始计时
	{
		end_time=0;
		begin_time=clock();
	}
	MOUSEMSG msg=GetMouseMsg();	
	int x,y;
	if(msg.y>60)
	{						
		switch(msg.uMsg)
		{	
			//左键点开，右键设置棋子		
			case WM_LBUTTONDOWN:
				x=msg.x/30;
				y=(msg.y-60)/30;
				if((JUD[x][y]==0||A[x][y]==10)&&qi[x][y]==0)
				{
					print(x,y,A[x][y]);
					if(A[x][y]==10) ctrl=2;	// 点击地雷
					if(A[x][y]==0) turn(x,y,A,JUD); // 点击空白
					if(A[x][y]!=0&&A[x][y]!=10) JUD[x][y]=1; // 点击数字
				}
				is_begin=true;					
				break;																					
		    case WM_RBUTTONDOWN:
				x=msg.x/30;
				y=(msg.y-60)/30;
				if(A[x][y]==10||JUD[x][y]==0)
				{
					if(qi[x][y]==1)
					{
				        qi[x][y]=0;
				        print(x,y,-2);
					}
					else
					{
						qi[x][y]=1;
						print(x,y,-1);
					}
				}
				is_begin=true;
				break;	
		}
	}	
}

void Game::is_end()
{
	setfillcolor(RGB(129,129,129));
	setlinecolor(RGB(129,129,129));
	fillrectangle(150,20,270,50);	
	
	if(end_time!=-1)end_time=clock();
	char buff[5] = { 0 };
	sprintf(buff, "%ds",(int)(end_time - begin_time)/CLOCKS_PER_SEC);
	settextcolor(RED);
	settextstyle(30,30,"楷体"); 
	setbkmode(TRANSPARENT);
	outtextxy(150,20,buff);
	
	int sum=1;
	for(int i=0;i<L;i++)
	{
		for(int j=0;j<W;j++)
		{
			sum*=JUD[i][j];
		}
	}
	if(sum==1)
	{
		ctrl=0;			
	}	
}

int main()
{
	Game*new_game=new Game;
	int ctrl=1;
	BeginBatchDraw();
	do
	{
		new_game->event_tick();
		new_game->is_end();
		FlushBatchDraw();
		ctrl=new_game->get_ctrl();
	}while(ctrl==1);
	EndBatchDraw();
	delete new_game;
	return 0;
}
















