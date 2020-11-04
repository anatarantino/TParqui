// Compile : 	gcc chess.c -o chess -Wall -pedantic -std=c99		Execute :	./chess

#include <graphics.h>
#include <chess_piece.h>
#include <prints.h>
#include <strings.h>
#include <timeRTC.h>

#define DIM 8

static int board[DIM][DIM] = { {2,3,4,6,5,4,3,2},
					{1,1,1,1,1,1,1,1},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{-1,-1,-1,-1,-1,-1,-1,-1},
					{-2,-3,-4,-6,-5,-4,-3,-2}};		// Positivos son blancos




// Piezas con sus posiciones iniciales y finales
int rook(int x0, int y0, int xf, int yf);		// 2 o -2
int horse(int x0, int y0, int xf, int yf);		// 3 o -3
int bishop(int x0, int y0, int xf, int yf);		// 4 o -4
int queen(int x0, int y0, int xf, int yf);		// 5 o -5
int king(int x0, int y0, int xf, int yf);		// 6 o -6
int pawn(int x0, int y0, int xf, int yf);		// 1 o -1

int gameover();
void printBoard();
void noPiece();
void initBoard();
void changePiece(int x, int y);
int checkFinalPos(int xf,int yf);
void check();
void timer(uint32_t startx, uint32_t starty, uint32_t endx, uint32_t endy, uint64_t bg_color);
void makeMove();
void rotateBoard();



int whoseTurn = 0;		// 0 es el turno de las blancas, 1 es el turno de las negras
int error;

static char log1[2000],log2[2000];
static int index1=0,index2=0;
static int segundosW = 0;
static int segundosB = 0;
static int aux = -1;
static int aux2;
static int rotation=0;

// Movimientos para validar el enroque
int kingMoves[] = {0,0};
int leftRooks[] = {0,0};
int rightRooks[] = {0,0};

int playNotEnded = 1;


void playChess(){

	//aux=getTime(SECONDS);
	
	while(!gameover()){
	
		drawBoard(board,0xB17C54,0xEED09D);
		//timer(40,40,100,100,0x000000);
		makeMove();

	}
	
	
}

void makeMove(){
	
	int x0, y0, xf, yf;
	int letra = getChar();
	if(letra=='r' || letra=='R'){
		rotateBoard();
		rotation = (rotation + 1) % 4;
		drawBoard(board,0xB17C54,0xEED09D);
		letra=getChar();
	}

	int nro = getChar();
	if(((letra >='A' && letra <= 'H') || (letra >= 'a' && letra <= 'h')) && (nro >= '1' && nro<= '8')){
		if(letra >='A' && letra <= 'H'){
			y0 = letra - 'A';
		}
		else{
			y0 = letra - 'a';
		}
		x0 = nro - '1';
		
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
		if(error!=1){
			if(whoseTurn==0){
				log1[index1++]=letra;
				log1[index1++]=nro;
				log1[index1++]=' ';
			}else{
				log2[index2++]=letra;
				log2[index2++]=nro;
				log2[index2++]=' ';
			}
		}
	}
	else{
		error = 1;
	}
	int letraF,nroF;
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
			int aux;
			switch(board[x0][y0]){
				case 1:
				case -1:
					if (rotation == 0){
						move = pawn(x0,y0,xf,yf);
					}else{
						move = pawn(y0,DIM-x0,yf,DIM-xf);
					}
					break;
					
				case 2:
				case -2:
					if (rotation == 0){
						move = rook(x0,y0,xf,yf);
					}else{
						move = rook(y0,DIM-x0,yf,DIM-xf);
					}
					break;
				case 3:
				case -3:
					if (rotation == 0){
						move = horse(x0,y0,xf,yf);
					}else{
						move = horse(y0,DIM-x0,yf,DIM-xf);
					}
					break;
				case 4:
				case -4:
					if (rotation == 0){
						move = bishop(x0,y0,xf,yf);
					}else{
						move = bishop(y0,DIM-x0,yf,DIM-xf);
					}
					break;
				case 5:
				case -5:
					if (rotation == 0){
						move = queen(x0,y0,xf,yf);
					}else{
						move = queen(y0,DIM-x0,yf,DIM-xf);
					}
					break;
				case 6:
				case -6:
					if (rotation == 0){
						move = king(x0,y0,xf,yf);
					}else{
						move = king(y0,DIM-x0,yf,DIM-xf);
					}
					break;
					
			}
			//printf("move: %d\n", move);         // si move ==0 que indique que lo que ingreso es incorrecto que pruebe escribir de nuevo
			if(move > 0){
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
		if(whoseTurn==0){
				log1[index1++]=letraF;
				log1[index1++]=nroF;
				log1[index1++]=' ';
		}else{
				log2[index2++]=letraF;
				log2[index2++]=nroF;
				log2[index2++]=' ';
		}
		printColorOnPos(log1,0xFFFFFF,0x000000,856,20);
		printColorOnPos(log2,0xDF02F1,0x000000,856,200);
		whoseTurn = (whoseTurn == 0)? 1:0;
		playNotEnded = 0;
	}
	error = 0;
	
}

void timer(uint32_t startx, uint32_t starty, uint32_t endx, uint32_t endy, uint64_t bg_color){
    int segundos=0;
    putChar('\n');
    putChar('\n');
     
    //int aux=getTime(SECONDS);
    //int aux2;
    //while(segundos<=3600){               // enter del jugador anterior
        aux2=getTime(SECONDS);
        if(aux!=aux2){
            segundos++;
            printIntOnPosColor(segundos, 0xFFFFFF,bg_color,startx,starty);
            aux=aux2;
        }
    //}
}

void noPiece(){	
	//printf("No hay una pieza en esa ubicacion, ingrese una nueva ubicacion\n");
	error = 1;
}

void changePiece(int x, int y){
	int wrongChar = 1;
	int c = getChar();
	while(wrongChar){
	//	//printf("Que pieza elige? q,b,h,r\n"); // q: queen, b: bishop, h: horse, r: rook
		c = getChar();
		switch(c){
			case 'q':
				board[x][y]= (whoseTurn==0)? 5:-5;
				wrongChar = 0;
				break;
			case 'b':
				board[x][y]= (whoseTurn==0)? 4:-4;
				wrongChar = 0;
				break;
			case 'h':
				board[x][y]= (whoseTurn==0)? 3:-3;
				wrongChar = 0;
				break;
			case 'r':
				board[x][y]= (whoseTurn==0)? 2:-2;
				wrongChar = 0;
				break;
			default:
				break;
				//printf("Pieza invalida\n");
		}
	}
	
}

int checkFinalPos(int xf, int yf){
	if(board[xf][yf] == 0 || (whoseTurn == 0 && board[xf][yf] < 0) || (whoseTurn == 1 && board[xf][yf] > 0)){
		return 1;
	}
	return 0;
}


// Movimientos	-> move = 1 si es un movimiento valido

// ROOK
int rook(int x0, int y0, int xf, int yf){
	int move=0;
	int i;

	if(y0==0){
		leftRooks[whoseTurn]=1;
	}else if(y0==7){
		rightRooks[whoseTurn]=1;
	}
	
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
			if(rook(x0,0,x0,y0-1) == 1 && board[x0][y0-1] == 0){	//no hay nada en el medio
				move = checkFinalPos(xf,yf);
				if(move == 1){
					board[x0][y0-1] = board[x0][0];
					board[x0][0] = 0;
				}
			}
			
		}
		else if(yf==y0+2 && rightRooks[whoseTurn] == 0){
			if(rook(x0,7,x0,y0+1) == 1 && board[x0][y0+1] == 0){	//no hay nada en el medio
				move = checkFinalPos(xf,yf);
				if(move == 1){
					board[x0][y0+1] = board[x0][7];
				board[x0][7] = 0;
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
	if(whoseTurn==0){		// blancas
		if(x0 == 1  && yf==y0 && xf == x0+2){
			if(board[x0+1][y0] == 0){
				move = checkFinalPos(xf,yf);
			}		
		}
		if(yf==y0 && xf == x0+1){
			move = checkFinalPos(xf,yf);
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
				move = checkFinalPos(xf,yf);
			}
		}
		if(yf==y0 && xf == x0-1){
			move = checkFinalPos(xf,yf);
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

void initBoard(){				// Arranca la parte grafica, los cuadros, las letras a los costados y los nros abajo

	// printf("A");	// cambia y, x se mantiene
	// printf("1");	// cambia x, y se mantiene

	//Esto se maneja con coordenadas de pixeles

}

void printBoard(){						// TO ERASE  (lo uso yo para imprimir y ver que funciona)
	//printf("A\tB\tC\tD\tE\tF\tG\tH\n");
	for(int i=0; i<DIM; i++){
		for(int j=0; j<DIM; j++){
			//printf("%d\t", board[i][j]);// switch case si es ==2 => que imprima torre blanca y asi

		}
	}
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

	if(player2 == 0){
		//printf("Player 2 wins\n");
		return 1;
	}

	if(player1 == 0){
		//printf("Player 1 wins\n");
		return 1;
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

void rotateBoard() {
    int ret[DIM][DIM]={0};

    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            ret[i][j] = board[DIM - j - 1][i];
        }
    }

    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            board[i][j] = ret[i][j];
        }
    }
}



