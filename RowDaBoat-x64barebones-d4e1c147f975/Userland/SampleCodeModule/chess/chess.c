#include <graphics.h>
#include <chess_piece.h>
#include <prints.h>
#include <strings.h>
#include <timeRTC.h>
#include <chess.h>
#include <lib.h>
#include <colors.h>

#define COLORP1 0xFFFFFF
#define COLORP2 0xF69F08

#define POSP1X 856
#define POSP2X 940
#define POSTITLEY 5
#define POSTIMERY 40
#define POSLOGSY 72
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
static int quit;
static int gameOver;
static int capture;
static int pawnCapture;
static char col;
static int castling;

int pawnMovesW[DIM];
int pawnMovesB[DIM];

// Movimientos para validar el enroque
int kingMoves[2];
int leftRooks[2];
int rightRooks[2];


void playChess(enum game_state state){
	
	if(state == new_game || (state == game_started && (init==0 ||gameover()))){
		init=1;
		initNewGame();
	}
	if(state == game_started){
		quit = 0;
		printColorOnPos(log1,COLORP1,BLACK,POSP1X,POSLOGSY);
		printColorOnPos(log2,COLORP2,BLACK,POSP2X,POSLOGSY);
	}
	
	
	
	while(!gameover() && !quit){
		drawBoard(board,0xB17C54,0xEED09D,rotation);
		printColorOnPos("Player 1:",COLORP1,BLACK,POSP1X,POSTITLEY);
		printColorOnPos(log1,COLORP1,BLACK,POSP1X,POSLOGSY);
		printColorOnPos("Player 2:",COLORP2,BLACK,POSP2X,POSTITLEY);
		printColorOnPos(log2,COLORP2,BLACK,POSP2X,POSLOGSY);
		makeMove();	

	}
	clearScreen();
	//poner quien gano y decir tipo apreta esc para salir o algo asi.
	
	
}

void makeMove(){
	
	int x0, y0, xf, yf;
	int letra=obtainChar();

	if(gameOver==1){
		exit();
		return;
	}

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

	int nro=obtainChar();

	if(gameOver==1){
		exit();
		return;
	}

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
		letraF=obtainChar();
		if(gameOver==1){
			exit();
			return;
		}
		nroF=obtainChar();
		
		if(gameOver==1){
			exit();
			return;
		}

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

			int piece = board[x0][y0];
			if((piece >= 10 && piece <=17)|| (piece >= -17 && piece <= -10)){
				move = pawn(x0,y0,xf,yf);
			}
			else if(piece == 2 || piece == -2){
				move = rook(x0,y0,xf,yf);
			}
			else if(piece == 3 || piece == -3){
				move = knight(x0,y0,xf,yf);
			}
			else if(piece == 4 || piece == -4){
				move = bishop(x0,y0,xf,yf);
			}
			else if(piece == 5 || piece == -5){
				move = queen(x0,y0,xf,yf);
			}
			else if(piece == 6 || piece == -6){
				move = king(x0,y0,xf,yf);
			}

			if(move > 0){
				piece=board[x0][y0];
				board[xf][yf] = board[x0][y0];
				board[x0][y0] = 0;
				if(move == 2 && !gameover()){
					col = changePiece(xf,yf);
				}
				check();
				blankPawnMoves();
			}
			else{
				error = 1;
			}

		}
	}
	
	if(error == 0){
		if(castling == 1){
			if(whoseTurn == 0){
				log1[index1++] = 'O';
				log1[index1++] = '-';
				log1[index1++] = 'O';
			}
			else{
				log2[index2++] = 'O';
				log2[index2++] = '-';
				log2[index2++] = 'O';
			}
		}
		else if(castling == 2){
			if(whoseTurn == 0){
				log1[index1++] = 'O';
				log1[index1++] = '-';
				log1[index1++] = 'O';
				log1[index1++] = '-';
				log1[index1++] = 'O';
			}
			else{
				log2[index2++] = 'O';
				log2[index2++] = '-';
				log2[index2++] = 'O';
				log2[index2++] = '-';
				log2[index2++] = 'O';
			}
		}
		else{
			if(pawnCapture == 1){
				if(whoseTurn == 0){
					log1[index1++] = col;
				}
				else{
					log2[index2++] = col;
				}
			}
			else{
				addPieceChar(piece);
				// if(letra>='a' && letra<='h'){
				// 	letra=letra - 'a'+'A';
				// }
			}
			
			if(whoseTurn==0){
					if(capture == 1){
						log1[index1++]='x';
					}
					log1[index1++]=letraF;
					log1[index1++]=nroF;
					log1[index1++]='\n';
			}else{
					if(capture == 1){
						log1[index2++]='x';
					}
					log2[index2++]=letraF;
					log2[index2++]=nroF;
					log2[index2++]='\n';
			}
		}
		if(pawnCapture == 2){
			if(whoseTurn == 0){
					log1[index1++] = '=';
					log1[index1++] = col;
					log1[index1++]='\n';
				}
				else{
					log2[index2++] = '=';
					log2[index2++] = col;
					log2[index2++]='\n';
				}
		}
		
		whoseTurn = (whoseTurn == 0)? 1:0;
		
		
	}
	error = 0;
	capture = 0;
	pawnCapture = 0;
	col = ' ';
	castling = 0;
	
}

char obtainChar(){
	int letra=0;
	while(letra==0){
		if(ticks_elapsed() % 18 == 0){
			if(whoseTurn==0){
				segundosW++;
				printTimer(segundosW,POSP1X,POSTIMERY,COLORP1,BLACK);
				if(segundosW-segundosB==60){
					gameOver=1;
					gameover();
					return -1;
				}
			}else{
				segundosB++;
				printTimer(segundosB,POSP2X,POSTIMERY,COLORP2,BLACK);
				if(segundosB-segundosW==60){
					gameOver=1;
					gameover();
					return -1;
				}
			}
		}
		letra=waitCharInterruption();
	}
	return letra;
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
        log1[index1++] = 'N';
        break;
    case -3:
        log2[index2++] = 'N';
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

char changePiece(int x, int y){
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
			case 'N':
			case 'n':
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
	
	return c;
}

int checkFinalPos(int xf, int yf){
	if(board[xf][yf] == 0){
		return 1;
	} else if((whoseTurn == 0 && board[xf][yf] < 0) || (whoseTurn == 1 && board[xf][yf] > 0)){
		capture = 1;
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
					capture = 0;
				}
			}
		}
		else{
			for(i=y0-1; i>yf;i--){
				if(board[x0][i] != 0){
					move = 0;
					capture = 0;
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
					capture = 0;
				}
			}
		}
		else{
			for(i=x0-1; i>xf;i--){
				if(board[i][y0] != 0){
					move = 0;
					capture = 0;
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
int knight(int x0, int y0, int xf, int yf){
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
					capture = 0;
				}
			}
		}
		else if(x0<xf && y0>yf){
			for(i=1; (x0+i)<xf;i++){
				if(board[x0+i][y0-i] != 0){
					move =0;
					capture = 0;
				}
			}
		}
		else if(x0>xf && y0>yf){
			for(i=1; (x0-i)>xf;i++){
				if(board[x0-i][y0-i] != 0){
					move =0;
					capture = 0;
				}
			}
		}
		else{
			for(i=1; (x0-i)<xf;i++){
				if(board[x0-i][y0+i] != 0){
					move =0;
					capture = 0;
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
	int attacked;
	int value = (whoseTurn == 0)? -1:1;
	if((xf==x0 &&(yf==y0+1 || yf==y0-1)) || (yf==y0 && (xf==x0+1 || xf == x0-1))){ //rook moves
		if(checkFinalPos(xf,yf)){
			if(!squareUnderAttack(xf,yf,value)){
				move = 1;
			}
			else{
				capture = 0;
			}
		}
		
	}
	else if((xf==x0+1 && yf==y0+1) || (xf==x0+1 && yf==y0-1) || (xf==x0-1 && yf==y0+1) || (xf==x0-1 && yf==y0-1)){	// bishop moves
		if(checkFinalPos(xf,yf)){
			if(!squareUnderAttack(xf,yf,value)){
				move = 1;
			}
			else{
				capture = 0;
			}
		}
	}

	//	enroque
	if(xf==x0 && kingMoves[whoseTurn]==0){
		if(yf==y0-2 && leftRooks[whoseTurn] == 0){					
			move = rook(x0,0,x0,y0-1);
			if(move == 1){	//no hay nada en el medio
				for(int i=0; i<=y0; i++){
					attacked = squareUnderAttack(x0,i, value);
					if(attacked == 1){
						break;
					}
				}
				if(!attacked){
					board[x0][y0-1] = board[x0][0];
					board[x0][0] = 0;
					castling = 2;
				}else{
					move = 0;
				}
				
			}
			
		}
		else if(yf==y0+2 && rightRooks[whoseTurn] == 0){
			move = rook(x0,7,x0,y0+1);
			if( move == 1){	//no hay nada en el medio
				for(int i=7; i>=y0; i--){
					attacked = squareUnderAttack(x0,i, value);
					if(attacked == 1){
						break;
					}
				}
				if(!attacked){
					board[x0][y0+1] = board[x0][7];
					board[x0][7] = 0;	
					castling = 1;
				}else{
					move = 0;
				}
						
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
	int pos;
	if(whoseTurn==0){		// blancas
		pos = board[x0][y0] - 10;
		if(x0 == 1  && yf==y0 && xf == x0+2){
			if(board[x0+1][y0] == 0 && board[xf][yf] == 0){
				move = 1;
				pawnMovesW[pos] = 1;
			}		
		}
		if(yf==y0 && xf == x0+1){
			move = (board[xf][yf] == 0)? 1:0;
		}
		if((yf==y0+1 || yf==y0-1) && xf == x0+1){
			pos = (board[x0][yf] * (-1)) - 10;
			if(board[xf][yf]<0){
				move = 1;
			}
			else if(x0==4 && board[x0][yf]<0 && pawnMovesB[pos] == 1){	// peon al paso
				board[x0][yf] = 0;
				move =1;
			}
			pawnCapture = 1;
			col = y0 + 'a';
			capture = 1;
		}

		// para el cambio de pieza
		if(move == 1 && xf==7){
			move = 2;
			pawnCapture = 2;
		}
	}
	else{		// negras
		pos = (board[x0][y0] * (-1)) - 10;
		if(x0 == 6  && yf==y0 && xf == x0-2){
			if(board[x0-1][y0] == 0 && board[xf][yf] == 0){
				move = 1;
				pawnMovesB[pos]=1;
			}
		}
		if(yf==y0 && xf == x0-1){
			move = (board[xf][yf] == 0)? 1:0;
		}
		if((yf==y0+1 || yf==y0-1) && xf == x0-1){
			pos = board[x0][yf] - 10;
			if(board[xf][yf]>0){
				move = 1;
			}
			else if(x0==3 && board[x0][yf]>0 && pawnMovesW[pos] == 1){	// peon al paso
				board[x0][yf] = 0;
				move = 1;
			}
			pawnCapture = 1;
			col = y0 + 'a';
			capture = 1;
		}

		// para el cambio de pieza
		if(move == 1 && xf==0){
			move = 2;
			pawnCapture = 2;
		}
	}

	return move;
}

int gameover(){
	int player1 = 0;
	int player2 = 0;
	if(gameOver==1){
		clearScreen();
		printColorOnPos("TIME OUT!",RED,BLACK,450,280);
		if(whoseTurn==0){
			printColorOnPos("GAME OVER PLAYER 2 WINS",RED,BLACK,390,300);
		}else{
			printColorOnPos("GAME OVER PLAYER 1 WINS",RED,BLACK,390,300);
		}
		return 1;
	}
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
			printColorOnPos("GAME OVER PLAYER 2 WINS",RED,BLACK,390,300);
		}

		if(player1 == 0){
			clearScreen();	
			printColorOnPos("GAME OVER PLAYER 1 WINS",RED,BLACK,390,300);
		}
		exit();
		return 1;
	}
	return 0;

}

void exit(){
	int escape;
	while(escape != 'x' && escape != 'X' && escape != 'n' && escape != 'N' ){
		escape = getChar();
	}
	if(escape == 'x' || escape == 'X' ){
		clearScreen();
	}else{
		playChess(new_game);
	}
}

void check(){
	int x,y;	// coordenadas del rey
	int i,j;	// contadores
	int check=0;
	if(whoseTurn==0){
		for(i=0; i<DIM; i++){
			for(j=0;j<DIM; j++){
				if(board[i][j]==-6){	// jaque al rey negro
					x=i;
					y=j;
					break;
				}
			}
		}
		check = squareUnderAttack(x,y,1);	// si hay piezas blancas atancando el casillero
	}
	else{
		for(i=0; i<DIM; i++){
			for(j=0;j<DIM; j++){
				if(board[i][j]==6){		// jaque al rey blanco
					x=i;
					y=j;
					break;
				}
			}
		}
		check = squareUnderAttack(x,y,-1);  // si hay piezas negras atancando el casillero
	}

	if(check==1){
		//printf("CHECK\n");
	}
}

int squareUnderAttack(int x, int y, int value){
	int attacked = 0;
	int b;
	for(int i=0; i<DIM; i++){
		for(int j=0; j<DIM; j++){
			b = board[i][j];
			if(b == 1*value){
				attacked=pawn(i,j,x,y);
			}
			else if(b == 2*value){
				attacked=rook(i,j,x,y);
			}
			else if(b == 3*value){
				attacked=knight(i,j,x,y);
			}
			else if(b == 4*value){
				attacked=bishop(i,j,x,y);
			}
			else if(b == 5*value){
				attacked=queen(i,j,x,y);
			}
		}
	}
	return attacked;
}

void initNewGame(){

	int auxBoard[][DIM] = { {2,3,4,6,5,4,3,2},
					{10,11,12,13,14,15,16,17},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{-10,-11,-12,-13,-14,-15,-16,-17},
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
	gameOver=0;
	capture = 0;
	pawnCapture = 0;
	col = ' ';
	castling = 0;
	// Movimientos para validar el enroque
	kingMoves[0] = 0; kingMoves[1] = 0;
	leftRooks[0] = 0; leftRooks[1] = 0;
	rightRooks[0] = 0; rightRooks[1] = 0;

	for(int i=0; i<DIM; i++){
		pawnMovesW[i] = 0;
		pawnMovesB[i] = 0;
	}


}

void printLogs(){
	clearScreen();
	printColorOnPos("Player 1:",COLORP1,BLACK,10,20);
	for(int i=0 ; i<index1 ; i++){
		if(log1[i]=='\n'){
			log1[i] = ' ';
		}
	}
	printColorOnPos(log1,COLORP1,BLACK,10,35);
	printColorOnPos("Player 2:",COLORP2,BLACK,10,350);
	for(int i=0 ; i<index2 ; i++){
		if(log2[i]=='\n'){
			log2[i] = ' ';
		}
	}
	printColorOnPos(log2,COLORP2,BLACK,10,365);
	for(int i=0 ; i<index1 ; i++){
		if(log1[i]==' '){
			log1[i] = '\n';
		}
	}
	for(int i=0 ; i<index2 ; i++){
		if(log2[i]==' '){
			log2[i] = '\n';
		}
	}
}

void blankPawnMoves(){
	if(whoseTurn == 0){
		for(int i=0; i<DIM; i++){
			pawnMovesB[i]=0;				// para evitar que el peon al paso se pueda realizar
		}									// en otra jugada que no sea la primera
	}
	else{
		for(int i=0; i<DIM; i++){
			pawnMovesW[i]=0;
		}
	}
}