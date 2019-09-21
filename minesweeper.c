#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MS_SIZE 8
#define MINE -1
#define FLAG 2
#define OPEN 1

int main(void)
{
    int mode;                      				//モードを保持
    int number_of_mines;                    			//地雷数のデフォルト値は10
    int mine_map[MS_SIZE][MS_SIZE];    			//地雷セルと数字セルを記録
    int game_board[MS_SIZE][MS_SIZE];   		//ゲームの進行を記録するためのゲームボード
    int i, j, k, l;
    int p1, p2, count, flag;
    int x, y;
    int fin;
    int cont;

    for(i=0; i<MS_SIZE; i++){                               //初期化
	for(j=0; j<MS_SIZE; j++){
	    game_board[i][j]=0;
	}
    }
    srand((unsigned)time(NULL)); 				//time関数で乱数を初期化する。
    printf("%d*%dのボードの各セルに配置された地雷を除去するゲームです。\n", MS_SIZE, MS_SIZE);
    printf("ゲームを始めます。\n");

    do{  							//ゲームプレイ続行の判断
	for(i=0; i<MS_SIZE; i++){                               //初期化
	    for(j=0; j<MS_SIZE; j++){
		mine_map[i][j]=0;
	    }
	}
	printf("地雷数を設定してください。(1~%d)： ",(MS_SIZE*MS_SIZE)-1);
	scanf("%d", &number_of_mines);
	while(number_of_mines==0 || number_of_mines>=MS_SIZE*MS_SIZE){
	    printf("地雷数が正しくありません\n");
	    printf("地雷数を設定してください。(1~%d)： ",(MS_SIZE*MS_SIZE)-1);
	    scanf("%d", &number_of_mines);
	}
	fin=0;

	for(i=0; i<number_of_mines; i++){			//地雷の設置
	    p1=rand()%MS_SIZE;
	    p2=rand()%MS_SIZE;
	    if(mine_map[p1][p2]==MINE){
		i--;
	    }
	    else{
		mine_map[p1][p2]=MINE;
	    }
	}

	for(i=0; i<MS_SIZE; i++){				//セル周囲の判定
	    for(j=0; j<MS_SIZE; j++){
		if(mine_map[i][j]==MINE){}
		else{
		    for(k=-1; k<2; k++){
			for(l=-1; l<2; l++){
			    if(i+k<0 || j+l<0 || i+k>(MS_SIZE-1) || j+l>(MS_SIZE-1)){}
			    else{
				if(mine_map[i+k][j+l] == MINE){
				    mine_map[i][j] += 1;
				}
			    }
			}
		    }
		}
	    }
	}

	while(fin==0){						//ゲームの継続条件
	    printf("モードを選択してください。：セルを開く(1)、フラグを設置/除去する(2)：  ");
	    scanf("%d", &mode);
	    while(mode!=1 && mode!=2){
		printf("1か2を入力してください。");
		scanf("%d", &mode);
	    }
	    //セルを開く
	    if(mode==1){
		printf("セルを開きます。\n");
		printf("行(x)と列(y)を入力してください。\n");
		scanf("%d %d", &x, &y);
		while((x<0 || MS_SIZE <= x)||(y<0 || MS_SIZE <= y)){	//セル内か判断
		    printf("行(x)と列(y)を入力してください。\n");
		    scanf("%d %d", &x, &y);
		}
		if(mine_map[x][y]==MINE){                         //地雷を選択した場合ゲームオーバー
		    printf("地雷を選択しました。ゲームオーバーです。\n");
		    fin=1;
		    break;
		    }
		else if(game_board[x][y]==OPEN ||game_board[x][y]==FLAG){
		    printf("既に開かれたマスまたは、旗が立っています。\n");
		}

		else{                                            //gameboardオープン
		    game_board[x][y]=OPEN;
		    for(k=-1; k<2; k++){
			for(l=-1; l<2; l++){
			    if(x+k<0 || y+l<0 || x+k>(MS_SIZE-1) || y+l>(MS_SIZE-1)){}
			    else{
				if(game_board[x+k][y+l]==FLAG){}
				else if(mine_map[x+k][y+l]!=MINE){
				    game_board[x+k][y+l]=OPEN;
				}
			    }
			}
		    }
		}
	    }

	    else {						//フラグを設置/除去する
		printf("フラグを設置/除去します。\n");
		printf("行(x)と列(y)を入力してください。\n");
		scanf("%d %d", &x, &y);
		while((x<0 || MS_SIZE <= x)||(y<0 || MS_SIZE <= y)){	//セル内か判断
		    printf("行(x)と列(y)を入力してください。\n");
		    scanf("%d %d", &x, &y);
		}
		if(game_board[x][y]==FLAG){			//旗が立っていたら除去
		    game_board[x][y]=0;
		}
		else{															                                                      //旗を設置
		    game_board[x][y]=FLAG;
		}
	    }

	                                                        //セルの表示
	    for(k=0; k<MS_SIZE; k++){
		printf("%2d|",k);
		for(l=0; l<MS_SIZE; l++){
		    if(game_board[k][l]==0){
			printf("  x");
		    }
		    else if(game_board[k][l]==OPEN){
			if(mine_map[k][l]==0){
			    printf("   ");
			}
			else {
			    printf("%3d",mine_map[k][l]);
			}
		    }
		    else if(game_board[k][l]==FLAG){		//旗はPとして表示
			printf("  P");
		    }
		}
		    printf("\n");
	    }
	    printf("  -------------------------\n");
	    printf("     0  1  2  3  4  5  6  7\n\n");

	    //ゲームクリアの判定
	    count=0;
	    flag=0;
	    for(i=0;i<MS_SIZE; i++){				//爆弾のところ全てに旗が立ったらクリア
		for(j=0; j<MS_SIZE; j++){
		    if(game_board[i][j]==FLAG){
			flag++;
		    }
		    if(mine_map[i][j]==MINE && game_board[i][j]==FLAG){
			count++;
		    }
		}
	    }
	    if(count==flag && flag>0){
		printf("ゲームクリアです！\nCongraturation\n");
		fin=1;
		break;
	    }


	    count=0;
	    for(i=0;i<MS_SIZE; i++){				//すべてのセルがオープンされたらクリア
		for(j=0; j<MS_SIZE; j++){
			if(game_board[i][j]==0){
			    count++;
			}
		}
	    }
    		if(count==0){
		    printf("ゲームクリアです！\nCongraturation\n");
		    fin=1;
		    break;
    		}
    	}

	printf("\n************結果***********\n\n");
	for(k=0; k<MS_SIZE; k++){				//セルの結果表示
	    printf("%2d|",k);
	    for(l=0; l<MS_SIZE; l++){
		if(mine_map[k][l]==MINE){
		    printf("  M");
		}
		else{
		    printf("%3d",mine_map[k][l]);
		}
	    }
	    printf("\n");
	}

	printf("  -------------------------\n");
	printf("     0  1  2  3  4  5  6  7\n\n");
	printf("Mが地雷\n\n");
	printf("ゲームを続行しますか？:Yes(1) :No(2) ： ");
	scanf("%d", &cont);
    }while(cont == 1);

    printf("ゲームを終了します。\n\n");

    return 0;
}
