// Compile : 	gcc chess.c -o chess -Wall -pedantic -std=c99		Execute :	./chess
#include <graphics.h>
#include <chess_piece.h>
#include <prints.h>
#include <strings.h>
#include <timeRTC.h>
#include <chess.h>

#define DIM 8

static int board[DIM][DIM];	// Positivos son blancos

int whoseTurn;		// 0 es el turno de las blancas, 1 es el turno de las negras
int error;
static char log1[2000],log2[2000];
static int index1,index2;
static uint64_t segundosW;
static uint64_t segundosB;
static int aux;
static int aux2;
static int rotation;
static int init = 0;
// Movimientos para validar el enroque
int kingMoves[2];
int leftRooks[2];
int rightRooks[2];
static int quit;

static int last_time;

void playChess(enum game_state state){
	
	if(state == new_game || (state == game_started && (init==0 ||gameover()))){
		init=1;
		initNewGame();
	}
	if(state == game_started){
		quit = 0;
		printColorOnPos(log1,0xFFFFFF,0x000000,856,20);
		printColorOnPos(log2,0x108520,0x000000,940,20);
	}
	//aux=getTime(SECONDS);
	
	
	while(!gameover() && !quit){
		drawBoard(board,0xB17C54,0xEED09D,rotation);
		printColorOnPos("Player 1:",0xFFFFFF,0x000000,856,5);
		printColorOnPos(log1,0xFFFFFF,0x000000,856,20);
		printColorOnPos("Player 2:",0x108520,0x000000,940,5);
		printColorOnPos(log2,0x108520,0x000000,940,20);
		//timer(40,40,100,100,0x000000);
		makeMove();	
		printIntOnPosColor(segundosW,0x0000FF,0x000000,0,20);

	}
	clearScreen();
	//poner quien gano y decir tipo apreta esc para salir o algo asi.
	
	
}

void makeMove(){
	
	int x0, y0, xf, yf;
	int letra = getCharWithTimer(&segundosW,0,0,0xFF0000,0x000000);
	if(letra=='s' || letra=='S'){ //spin (r reserved for rook)
		rotation = (rotation + 1) % 4;
		drawBoard(board,0xB17C54,0xEED09D,rotation);
		return;
	}
	if(letra == 'x' || letra == 'X'){
		quit=1;
		return;
	}

	if(letra == 'l' || letra == 'L'){
		int escape;
		printLogs();
		while(escape != 'l' && escape != 'L' && escape!='x' && escape != 'X' ){
			escape=getChar();
		}
		if(escape=='x' || escape == 'X'){
			quit=1;
			return;
		}
		clearScreen();
		return;
		
	}

	int nro = getChar();
	int aux4;

	if(((letra >= 'A' && letra <= 'H') || (letra >= 'a' && letra <= 'h')) && (nro >= '1' && nro<= '8')){
		
		if(letra >='A' && letra <= 'H'){
			y0 = letra - 'A';
		}
		else{
			y0 = letra - 'a';
		}
		x0 = nro - '1';
		if(rotation==1){
			aux4=x0;
			x0=DIM-y0-1;
			y0=aux4;
		}else if(rotation==2){
			x0=DIM-1-x0;
			y0=DIM-1-y0;
		}else if(rotation==3){
			aux4=x0;
			x0=y0;
			y0=DIM-1-aux4;
		}

		if(board[x0][y0] == 0){		// no selecciono ninguna pieza
			noPiece();
			x0 = -1;
			y0 = -1;
		}
		else{
			if(whoseTurn == 0){
				if(board[x0][y0] <0){	// selecciono una pieza negra
					noPiece();
					x0 = -1;
					y0 = -1;
				}
			}
			else{
				if(board[x0][y0] > 0){	// selecciono una pieza blanca
					noPiece();
					x0 = -1;
					y0 = -1;
				}
			
			}
		}
	}
	else{
		error = 1;
	}
	int letraF,nroF, piece;
	if(x0 != -1 && y0 != -1 && error!=1){		//selecciono una pieza valida
		letraF = getChar();
		nroF = getChar();

		if(((letraF >='A' && letraF <= 'H') || (letraF >= 'a' && letraF <= 'h')) && (nroF >= '1' && nroF <= '8')){
			if(letraF >='A' && letraF <= 'H'){
				yf = letraF - 'A';
			}
			else{
				yf = letraF - 'a';
			}
			xf = nroF-'1';
		}
		else{
			error = 1;
		}
		if(error!=1){
			int move = 0;
			if(rotation==1){
				aux4=xf;
				xf=DIM-yf-1;
				yf=aux4;
			}else if(rotation==2){
				xf=DIM-1-xf;
				yf=DIM-1-yf;
			}else if(rotation==3){
				aux4=xf;
				xf=yf;
				yf=DIM-1-aux4;
			
			}

			switch(board[x0][y0]){
				case 1:
				case -1:
					move = pawn(x0,y0,xf,yf);
					break;			
				case 2:
				case -2:
					move = rook(x0,y0,xf,yf);
					break;
				case 3:
				case -3:
					move = horse(x0,y0,xf,yf);
					break;
				case 4:
				case -4:
					move = bishop(x0,y0,xf,yf);
					break;
				case 5:
				case -5:
					move = queen(x0,y0,xf,yf);
					break;
				case 6:
				case -6:
					move = king(x0,y0,xf,yf);
					break;
			}
			if(move > 0){
				piece=board[x0][y0];
				board[xf][yf] = board[x0][y0];
				board[x0][y0] = 0;
				if(move == 2){
					changePiece(xf,yf);
				}
				check();
			}
			else{
				error = 1;
			}

		}
	}
	
	if(error == 0){
		addPieceChar(piece);
		if(letra>='a' && letra<='h'){
			letra=letra - 'a'+'A';
		}
		if(whoseTurn==0){
				log1[index1++]=letraF;
				log1[index1++]=nroF;
				log1[index1++]='\n';
		}else{
				log2[index2++]=letraF;
				log2[index2++]=nroF;
				log2[index2++]='\n';
		}
		printColorOnPos(log1,0xFFFFFF,0x000000,856,20);
		printColorOnPos(log2,0x108520,0x000000,940,20);
		whoseTurn = (whoseTurn == 0)? 1:0;
		
	}
	error = 0;
	
}

void addPieceChar(int number){
    switch (number)
    {
    case 2:
        log1[index1++] = 'R';
        break;
    case -2:
        log2[index2++] = 'R';
        break;
    case 3:
        log1[index1++] = 'H';
        break;
    case -3:
        log2[index2++] = 'H';
        break;
    case 4:
        log1[index1++] = 'B';
        break;
    case -4:
        log2[index2++] = 'B';
        break;
    case 5:
        log1[index1++] = 'Q';
        break;
    case -5:
        log2[index2++] = 'Q';
        break;
    case 6:
        log1[index1++] = 'K';
        break;
    case -6:
        log2[index2++] = 'K';
        break;
    default:
        break;
    }
}


void noPiece(){	
	error = 1;
}

void changePiece(int x, int y){
	int wrongChar = 1;
	int c = getChar();
	while(wrongChar){
		switch(c){
			case 'Q':
			case 'q':									
				board[x][y]= (whoseTurn==0)? 5:-5;
				wrongChar = 0;
				break;
			case 'B':
			case 'b':
				board[x][y]= (whoseTurn==0)? 4:-4;
				wrongChar = 0;
				break;
			case 'H':
			case 'h':
				board[x][y]= (whoseTurn==0)? 3:-3;
				wrongChar = 0;
				break;
			case 'R':
			case 'r':
				board[x][y]= (whoseTurn==0)? 2:-2;
				wrongChar = 0;
				break;
			default:
				c = getChar();
				break;
		}
	}
	
}

int checkFinalPos(int xf, int yf){
	if(board[xf][yf] == 0 || (whoseTurn == 0 && board[xf][yf] < 0) || (whoseTurn == 1 && board[xf][yf] > 0)){
		return 1;
	}
	return 0;
}


// ROOK
int rook(int x0, int y0, int xf, int yf){
	int move=0;
	int i;
	
	if(x0 == xf){
		move = checkFinalPos(xf,yf);
		if(y0<yf){						//empieza a chequear que no se choca con otras piezas
			for(i=y0+1; i<yf;i++){
				if(board[x0][i] != 0){
					move = 0;
				}
			}
		}
		else{
			for(i=y0-1; i>yf;i--){
				if(board[x0][i] != 0){
					move = 0;
				}
			}
		}
	}
	else if(y0 == yf){
		move = checkFinalPos(xf,yf);
		if(x0<xf){						//empieza a chequear que no se choca con otras piezas
			for(i=x0+1; i<xf;i++){
				if(board[i][y0] != 0){
					move = 0;
				}
			}
		}
		else{
			for(i=x0-1; i>xf;i--){
				if(board[i][y0] != 0){
					move = 0;
				}
			}
		}
	}

	if(move == 1){
		if(y0==0){
			leftRooks[whoseTurn]=1;
		}else if(y0==7){
			rightRooks[whoseTurn]=1;
		}	
	}
	return move;
}
	
// HORSE
int horse(int x0, int y0, int xf, int yf){
	int move=0;
	if((xf==x0+2 && (yf==y0+1 || yf == y0-1)) 	||	(xf==x0-2 && (yf==y0+1 || yf == y0-1)) 
		||	(yf==y0+2 && (xf==x0+1 || xf == x0-1))	||	(yf==y0+2 && (xf==x0+1 || xf == x0-1))){
		move = checkFinalPos(xf,yf);
	}
	return move;
}

// BISHOP
int bishop(int x0, int y0, int xf, int yf){
	int move=0;
	int constant = xf - x0;
	int i;
	if(yf==y0+constant || yf==y0-constant){	
		move = checkFinalPos(xf,yf);
		if(x0<xf && y0<yf){						//empieza a chequear que no se choca con otras piezas
			for(i=1; (x0+i)<xf;i++){
				if(board[x0+i][y0+i] != 0){
					move =0;
				}
			}
		}
		else if(x0<xf && y0>yf){
			for(i=1; (x0+i)<xf;i++){
				if(board[x0+i][y0-i] != 0){
					move =0;
				}
			}
		}
		else if(x0>xf && y0>yf){
			for(i=1; (x0-i)>xf;i++){
				if(board[x0-i][y0-i] != 0){
					move =0;
				}
			}
		}
		else{
			for(i=1; (x0-i)<xf;i++){
				if(board[x0-i][y0+i] != 0){
					move =0;
				}
			}
		}

	}

	return move;
}

// QUEEN
int queen(int x0, int y0, int xf, int yf){
	int move =0;
	move = rook(x0,y0,xf,yf);			// si la reina se mueve en linea recta
	move += bishop(x0,y0,xf,yf);			// si la reina se mueve en diagonal
	return move;
}

// KING
int king(int x0, int y0, int xf, int yf){
	int move=0;
	if((xf==x0 &&(yf==y0+1 || yf==y0-1)) || (yf==y0 && (xf==x0+1 || xf == x0-1))){ //rook moves
		move = checkFinalPos(xf,yf);
	}
	else if((xf==x0+1 && yf==y0+1) || (xf==x0+1 && yf==y0-1) || (xf==x0-1 && yf==y0+1) || (xf==x0-1 && yf==y0-1)){	// bishop moves
		move = checkFinalPos(xf,yf);
	}

	//	enroque
	if(xf==x0 && kingMoves[whoseTurn]==0){
		if(yf==y0-2 && leftRooks[whoseTurn] == 0){					//HAY QUE VER QUE NO HAYA NADA "ATACANDO" EL MEDIO O LAS FIGURAS
			move = rook(x0,0,x0,y0-1);
			if(move == 1){	//no hay nada en el medio
				board[x0][y0-1] = board[x0][0];
				board[x0][0] = 0;
			}
			
		}
		else if(yf==y0+2 && rightRooks[whoseTurn] == 0){
			move = rook(x0,7,x0,y0+1);
			if( move == 1){	//no hay nada en el medio
				board[x0][y0+1] = board[x0][7];
				board[x0][7] = 0;			
			}
		}
	}

	if(move == 1){
		kingMoves[whoseTurn] = 1;
	}
	return move;
}

// PAWN
int pawn(int x0, int y0, int xf, int yf){
	int move=0;
	if(whoseTurn==0){		// blancas
		if(x0 == 1  && yf==y0 && xf == x0+2){
			if(board[x0+1][y0] == 0){
				move = (board[xf][yf] == 0)? 1:0;
			}		
		}
		if(yf==y0 && xf == x0+1){
			move = (board[xf][yf] == 0)? 1:0;
		}
		if((yf==y0+1 || yf==y0-1) && xf == x0+1){
			if(board[xf][yf]<0){
				move = 1;
			}
			else if(x0==4 && board[x0][yf]<0){	// peon al paso
				board[x0][yf] = 0;
				move =1;
			}
		}

		// para el cambio de pieza
		if(move == 1 && xf==7){
			move = 2;
		}
	}
	else{		// negras
		if(x0 == 6  && yf==y0 && xf == x0-2){
			if(board[x0-1][y0] == 0){
				move = (board[xf][yf] == 0)? 1:0;
			}
		}
		if(yf==y0 && xf == x0-1){
			move = (board[xf][yf] == 0)? 1:0;
		}
		if((yf==y0+1 || yf==y0-1) && xf == x0-1){
			if(board[xf][yf]>0){
				move = 1;
			}
			else if(x0==3 && board[x0][yf]>0){	// peon al paso
				board[x0][yf] = 0;
				move = 1;
			}
		}

		// para el cambio de pieza
		if(move == 1 && xf==0){
			move = 2;
		}
	}

	return move;
}

int gameover(){
	int player1 = 0;
	int player2 = 0;
	for(int i=0; i<DIM; i++){
		for(int j=0; j<DIM; j++){
			if(board[i][j] == 6){
				player2 =1;
			}
			else if(board[i][j] == -6){
				player1 =1;
			}
		}
	}
	if(player1 == 0 || player2==0){
		if(player2 == 0){
			clearScreen();
			printColorOnPos("GAME OVER PLAYER 2 WINS",0xFF0000,0x000000,320,300);
			printColorOnPos("[press X to quit game or N to start a new one]",0xFF0000,0x000000,250,330);
			
			//return 1;
		}

		if(player1 == 0){
			clearScreen();	
			printColorOnPos("GAME OVER PLAYER 1 WINS",0xFF0000,0x000000,320,300);
			printColorOnPos("[press X to quit game or N to start a new one]",0xFF0000,0x000000,250,330);
			//return 1;
		}
		int escape;
		while(escape != 'x' && escape != 'X' && escape != 'n' && escape != 'N' ){
			escape = getChar();
		}
		if(escape == 'x' || escape != 'X' ){
			clearScreen();
			return 1;
		}
	}
	return 0;

}

void check(){
	int x,y;	// coordenadas del rey
	int i,j;	// contadores
	int check=0;
	if(whoseTurn==0){
		for(i=0; i<DIM; i++){
			for(j=0;j<DIM; j++){
				if(board[i][j]==-6){
					x=i;
					y=j;
					break;
				}
			}
		}
		for(i=0; i<DIM; i++){
			for(j=0; j<DIM; j++){
				switch(board[i][j]){
					case 1:
						check=pawn(i,j,x,y);
						break;
					case 2:
						check=rook(i,j,x,y);
						break;
					case 3:
						check=horse(i,j,x,y);
						break;
					case 4:
						check=bishop(i,j,x,y);
						break;
					case 5:
						check=queen(i,j,x,y);
						break;
				}
				
			}
		}
	}
	else{
		for(i=0; i<DIM; i++){
			for(j=0;j<DIM; j++){
				if(board[i][j]==6){
					x=i;
					y=j;
					break;
				}
			}
		}
		for(i=0; i<DIM; i++){
			for(j=0; j<DIM; j++){
				switch(board[i][j]){
					case -1:
						check=pawn(i,j,x,y);
						break;
					case -2:
						check=rook(i,j,x,y);
						break;
					case -3:
						check=horse(i,j,x,y);
						break;
					case -4:
						check=bishop(i,j,x,y);
						break;
					case -5:
						check=queen(i,j,x,y);
						break;
				}
			}
		}
		
	}
	if(check==1){
		//printf("CHECK\n");
	}
}

void initNewGame(){

	int auxBoard[][DIM] = { {2,3,4,6,5,4,3,2},
					{1,1,1,1,1,1,1,1},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{-1,-1,-1,-1,-1,-1,-1,-1},
					{-2,-3,-4,-6,-5,-4,-3,-2}};
	
	for(int i=0; i<DIM ;i++){
		for(int j=0 ; j<DIM ; j++){
			board[i][j]=auxBoard[i][j];
		}
	}

	for(int i=0 ; i<index1 ; i++){
		log1[i]=0;
	}
	for(int i=0 ; i<index2 ; i++){
		log2[i]=0;
	}
	index1=0;
	index2=0;
	whoseTurn = 0;		// 0 es el turno de las blancas, 1 es el turno de las negras
	error;
	char log1[2000],log2[2000];
	index1=0,index2=0;
	segundosW = 0;
	segundosB = 0;
	aux = -1;
	aux2;
	rotation=0;
	quit = 0;
	// Movimientos para validar el enroque
	kingMoves[0] = 0; kingMoves[1] = 0;
	leftRooks[0] = 0; leftRooks[1] = 0;
	rightRooks[0] = 0; rightRooks[1] = 0;

}

void printLogs(){
	clearScreen();
	printf("plays until now: [press L to continue game or X to exit]");
	printColorOnPos("Player 1:",0xFFFFFF,0x000000,10,20);
	for(int i=0 ; i<index1 ; i++){
		if(log1[i]=='\n'){
			log1[i] = ' ';
		}
	}
	printColorOnPos(log1,0xFFFFFF,0x000000,10,35);
	printColorOnPos("Player 2:",0x108520,0x000000,10,350);
	for(int i=0 ; i<index2 ; i++){
		if(log2[i]=='\n'){
			log2[i] = ' ';
		}
	}
	printColorOnPos(log2,0xFFFFFF,0x000000,10,365);
	
}