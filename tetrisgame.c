#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void show_menu(int highest_score);  //Menuyu gosteren fonksiyon, ayni zamanda highest score'u gosteriyor.

void game_over_message(); //Oyun bitince karsimiza cikacak yaziyi yazdiran fonksiyon.

void exit_game_message(); //Oyundan tamamen cikinca karsimiza cikacak yaziyi yazdiran fonksiyon.

int **create_board(int row, int column); //dynamic memory allocation ile board olusturacak fonksiyon.

void free_board(int **board,int rows); //olusturdugumuz board'i bellekten serbest birakmak icin fonksiyon.

void show_board(int **board,int rows,int column); //Board'i gosteren fonksiyon.

void show_piece(int piece[3][3]); //Gelen random parcayi gosteren fonksiyon.

int play_game(); //Oyunu oynatan fonksiyon.

void rotate_piece(int temp_piece[3][3]); //parca donduren fonksiyon.(bu fonksiyonla alakali onemli bir bilgiyi asagida aciklayacagim.)

int check_carpisma(int **board,int piece[3][3],int row,int real_row, int col,int x_coordinate); //carpisma var mi yok mu kontrol eden fonksiyon.

int check_place(int piece[3][3],int **board,int row,int real_row, int column,int x_coordinate); //parcayi uygun yere yerlestiren fonksiyon.

void remove_rows_if_full(int **board,int row,int column, int *score); //satir doluysa o satiri yok eden ve ustundekileri bir asagi kaydiran fonksiyon.

void copy_pieces(int piece[3][3],int temp_piece[3][3]); //bir parcayi kopyalamak icin fonksiyon( parcayi dondurunce asil hali kaybolmasin diye.)

void shift_left(int piece[3][3]); //Oyunumuz gercek zamanli olmadigi icin ve parca dondurmesini matrisi 90 derece saat yonunde cevirme olarak yaptigim icin ve kullanici sol ust koseyi yerlestirmek istedigi icin benim algoritmam geregi matrisi dondurunce sola yaslamamiz sart.


int main(){
    int start_exit;
    int highest_score = 0,score = 0;
    do{
        
        do{
            
            show_menu(highest_score);
            if(scanf("%d",&start_exit) != 1){ //kullanici harf falan girerse diye program buglanmasin diye kontrol.
                scanf("%*s");
                start_exit = -1;
                
            }
            printf("\033[H\033[J");
        }while(start_exit != 1 && start_exit != 2);

        if(start_exit == 1){
            score = play_game();
            if(score > highest_score){
                highest_score = score;
            }
        }
        else if(start_exit == 2){
            exit_game_message();
        }
    }while(start_exit !=2);

   return 0;
}

void show_menu(int highest_score){
    printf("_________          _______     ______   _______  _______ _________    _______  _______  _______  _______ \n");
    printf("\\__   __/|\\     /|(  ____ \\   (  ___ \\ (  ____ \\(  ____ \\\\__   __/   (  ____ \\(  ___  )(       )(  ____ \\\n");
    printf("   ) (   | )   ( || (    \\/   | (   ) )| (    \\/| (    \\/   ) (      | (    \\/| (   ) || () () || (    \\/\n");
    printf("   | |   | (___) || (__       | (__/ / | (__    | (_____    | |      | |      | (___) || || || || (__    \n");
    printf("   | |   |  ___  ||  __)      |  __ (  |  __)   (_____  )   | |      | | ____ |  ___  || |(_)| ||  __)   \n");
    printf("   | |   | (   ) || (         | (  \\ \\ | (            ) |   | |      | | \\_  )| (   ) || |   | || (      \n");
    printf("   | |   | )   ( || (____/\\   | )___) )| (____/\\/\\____) |   | |      | (___) || )   ( || )   ( || (____/\\ \n");
    printf("   )_(   |/     \\|(_______/   |/ \\___/ (_______/\\_______)   )_(      (_______)|/     \\||/     \\|(_______/\n");


    printf("                             _           _ \n");
    printf("                            | |         | |\n");
    printf("          ___ _ __ ___  __ _| |_ ___  __| |\n");
    printf("         / __| '__/ _ \\/ _` | __/ _ \\/ _` |\n");
    printf("        | (__| | |  __/ (_| | ||  __/ (_| |\n");
    printf("         \\___|_|  \\___|\\__,_|\\__\\___|\\__,_|\n");
     printf("              __           \n");
    printf("              | |          \n");
    printf("              | |__  _   _ \n");
    printf("              | '_ \\| | | |\n");
    printf("              | |_) | |_| |\n");
    printf("              |_.__/ \\__, |\n");
    printf("                      __/ |\n");
    printf("                     |___/ \n");






    printf("                     _    _ _    _  _____ ________     _______ _   _ \n");
    printf("                    | |  | | |  | |/ ____|  ____\\ \\   / /_   _| \\ | |\n");
    printf("                    | |__| | |  | | (___ | |__   \\ \\_/ /  | | |  \\| |\n");
    printf("                    |  __  | |  | |\\___ \\|  __|   \\   /   | | | . ` |\n");
    printf("                    | |  | | |__| |____) | |____   | |   _| |_| |\\  |\n");
    printf("                    |_|  |_|\\____/|_____/|______|  |_|  |_____|_| \\_|\n");
    printf("\n");

    printf("#################################################################################################################\n\n\n");
    printf("***************************** CURRENT HIGHEST SCORE: $ %d $  *****************************************************\n\n",highest_score);

    printf("  __    _____ _______       _____ _______ _____          __  __ ______ \n");
    printf(" /_ |  / ____|__   __|/\\   |  __ \\__   __/ ____|   /\\   |  \\/  |  ____|\n");
    printf("  | | | (___    | |  /  \\  | |__) | | | | |  __   /  \\  | \\  / | |__   \n");
    printf("  | |  \\___ \\   | | / /\\ \\ |  _  /  | | | | |_ | / /\\ \\ | |\\/| |  __|  \n");
    printf("  | |  ____) |  | |/ ____ \\| | \\ \\  | | | |__| |/ ____ \\| |  | | |____ \n");
    printf("  |_| |_____/   |_/_/    \\_\\_|  \\_\\ |_|  \\_____/_/    \\_\\_|  |_|______|\n");
    printf("\n");
    printf(" ___     ________   _______ _______ \n");
    printf("|__ \\   |  ____\\ \\ / /_   _|__   __|\n");
    printf("   ) |  | |__   \\ V /  | |    | |   \n");
    printf("  / /   |  __|   > <   | |    | |   \n");
    printf(" / /_   | |____ / . \\ _| |_   | |   \n");
    printf("|____|  |______/_/ \\_\\_____|  |_|   \n");


}

void game_over_message(){
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("                          _____          __  __  ____     ______      _________ ____  \n");
    printf("                         / ____|   /\\   |  \\/  ||  __|   / __ \\ \\    / /  ____|  __ \\ \n");
    printf("                        | |  __   /  \\  | \\  / || |__   | |  | \\ \\  / /| |__  | |__) |\n");
    printf("                        | | |_ | / /\\ \\ | |\\/| ||  __|  | |  | |\\ \\/ / |  __| |  _  / \n");
    printf("                        | |__| |/ ____ \\| |  | || |__   | |__| | \\  /  | |____| | \\ \\ \n");
    printf("                         \\_____/_/    \\_\\_|  |_||____|   \\____/   \\/   |______|_|  \\_\\ \n");

    printf("\n\n                                                                Press any key to continue...\n");
    getchar();
    getchar(); //kullanici bir tusa basana kadar game over yazisi gorur
}
void exit_game_message(){
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("                  _____  ____   ____  _____  ______     ________           \n");
    printf("                 / ____|/ __ \\ / __ \\|  __ \\|  _ \\ \\   / /  ____|          \n");
    printf("                | |  __| |  | | |  | | |  | | |_) \\ \\_/ /| |__             \n");
    printf("                | | |_ | |  | | |  | | |  | |  _ < \\   / |  __|            \n");
    printf("                | |__| | |__| | |__| | |__| | |_) | | |  | |____ _ _ _ _ _ \n");
    printf("                 \\_____|\\____/ \\____/|_____/|____/  |_|  |______(_|_|_|_|_)\n");
}
int **create_board(int row, int column){
    int i;
    int **board = (int**)calloc(row,sizeof(int*));
    if(board == NULL){ //yer ayrilamazsa hata kontrolu
        printf("Failed to allocate memory for board.\n");
        exit(1);
    }
    for(i = 0;i<row;i++){
        board[i] = (int*)calloc(column,sizeof(int));
        if(board[i] == NULL){
            printf("Failed to allocate memory for board.\n"); //yine yer ayrilamazsa hata kontrolu
            exit(1);
        }
    }
    return board;
    
}
void free_board(int **board, int rows){
    int i;
    for(i = 0;i<rows;i++){
        free(board[i]);
    }
    free(board);
}

void show_board(int **board,int rows,int column){
    int i,j;
    printf("\n");
    for(i = 0;i<rows;i++){
        
        for(j = 0;j<column;j++){
            if (i == 0 || i == rows - 1 || j == 0 || j == column - 1) {
                printf("$ "); //board'in sinirlarini $ sembolu ile dolduruyoruz.
            }
            else if(board[i][j] == 1){
                printf("1 ");
            }
            else {
                printf(". ");
            }
            
        }
        printf("\n");
    }
    printf("X|");
    for (i = 1; i <= column-2; i++) {
        printf("%d ", i%10);
    }
    printf("|\n");

}
void show_piece(int piece[3][3]){
    printf("Current piece:\n");
    int i,j;
    for(i = 0;i<3;i++){
        printf("   ");
        for(j = 0;j<3;j++){
            if(piece[i][j] == 1){
                printf("1 ");
            }
            
            else {
                printf("  "); // Parca matrisinde sadece 1 degerleri gozukecek
            }
        }
        if(piece[i][0] == 1 || piece[i][1] == 1 || piece[i][2] == 1 ){//parcanin herhangi bir satiri doluysa asagi iniyor.
            printf("\n");  
        }
            
    }
    printf("\n");
    printf("Press 'R' to Rotate, Press 'P' to Put");
    printf("\n");
   
}

void rotate_piece(int temp_piece[3][3]){//Matrisi 90 derece donduren fonksiyon bu fonksiyon icin aciklamam onemli:
//bu fonksiyonu tum parcalarin tum donmus versiyonlu hallerini zaten hali hazirda verip, yeteri kadar if kullanarak bir parcaya donme komutu verilince onun dondurulmus haline yollayabilirdik-
//Hatta bu sekilde yapmak daha hizli calisan bir dondurme saglardi. Ancak o yontem cok hard coding olurdu. Mesela bu benim yaptigim yontemle, yeni parca eklenmek istediginde sadece parcalar-
//dizisine 1 adet parcanin eklenmesi yeterli, baska bir sey degistrimeye gerek yok. Evet yeteri kadar if kullanarak, dondurme komutu geldiginde parcalari parcalarin dondurulmus hallerine yonlendirmek-
//daha hizli bir calisma saglar ancak hard coding olmus olur bu yuzden tercih etmedim. Matrisi 90 derece dondurmek daha guzel!!

    int i,j,temp;
    for(i  = 0;i<3;i++){ //matrisin transpozesini aliyoruz.
        for(j = i+1;j<3;j++){
            temp = temp_piece[i][j];
            temp_piece[i][j] = temp_piece[j][i];
            temp_piece[j][i] = temp;
        }
    }

    for(i  = 0;i<3;i++){ //matris yatay simetrisi 90 derece donmus olacak sonrasinda
        for(j = 0;j<1.5;j++){
            temp = temp_piece[i][j];
            temp_piece[i][j] = temp_piece[i][2-j];
            temp_piece[i][2-j] = temp;
            
        }
    }
    
    
}
void remove_rows_if_full(int **board,int row,int column, int *score){
    int sum,i,j,full_row_count = 0,x,y;
    for(i = 1;i<=row;i++){ //boardin cevresi sekillerle kapli oldugu icin 1'den basliyorum.
        sum = 0;
        for(j = 1;j<=column;j++){
            sum += board[i][j]; //boardin bir satirindaki tum sutunlari topluyoruz
        }
        if(sum == column){ //satir doluysa bu if'e girecek.
            full_row_count++;
            for(x = i;x>= 2;x--){ //2'den buyuk veya esit olmali cunku 1. satirin ustunde baska satir yok
                for(y = 1;y<=column;y++){
                    board[x][y] = board[x-1][y]; //dolu satirin ustundeki asagi dusecek.
                }
            }
            for(y = 0;y<= column;y++){
                board[x][y] = 0;  //satiri bosalt.
            }
            *score += sum*full_row_count; //puanlari ekle. bu islemi burada yapma sebebim, ne kadar coklu satir ayni anda patlatirsa o kadar cok puan alacak-
            //Mesela 2 satir ayni anda patlatirsa sanki 3 tane tekli satir patlatmis gibi puan aliyor. Yani ne kadar cok satir ayni anda patlatirsa o kadar cok puan almasi icin burda yazdim.
            //esit olmasini istesem for disinda full_row_count ile carpardim.
        }
       
    }
}

void copy_pieces(int piece[3][3],int temp_piece[3][3]){ //parca kopyalamak icin. dondurunce asil parcamiz kaybolmasin.(dondurme fonksiyonunu niye matris dondurmesi yaptigimi acikladim.)
    int i,j;
    for(i = 0;i<3;i++){
        for(j = 0;j<3;j++){
            temp_piece[i][j] =  piece[i][j];
        }
    }
}

int check_carpisma(int **board,int piece[3][3],int row,int real_row, int col,int x_coordinate){ //carpisma kontrolu sagliyor. carpisma yoksa 0 donuyor.
    int i,j;
    for(i = 0;i<3;i++){
        for(j = 0;j<3;j++){
            if(piece[i][j]){
                if(j+x_coordinate>col){
                    return -1;//boardin disina cikan parcalar konulamaz. bunun kontrolu
                }
                else if((row+i > real_row) || board[row+i][x_coordinate+j]){ //boarddaki parcalarla bizim parcamiz cakisiyor mu?
                    return -5;
                }
            }
        }
    }
    return 0;
}

int check_place(int piece[3][3],int **board,int row,int real_row, int column,int x_coordinate){
        int control= 1,i,j;
        row = 1;
        control = check_carpisma(board,piece,row,real_row,column,x_coordinate); //carpisma yoksa donguye gir.
        while((row<=real_row) && (control ==0)){
            row++; //parca yukaridan birakilmis gibi simule ediliyor ve surekli asagiya dogru dusuyor
            control = check_carpisma(board,piece,row,real_row,column,x_coordinate); //carpisma oldugu an artik parca asagi dusmuyor ve uygun bolgeye yerlesecek.

        }
        if(control == -1){ //kullanici boardin disina mi koymaya calisti kontrolu.

            return control;
        }
        row--;
        if(row == 0){ //Bir parca matrisindeki herhangi '1' ifadesi board ust sinirini gectiyse oyun biter.
            return -11;
        }
        
        for(i = 0;i<3;i++){
            for(j = 0;j<3;j++){
                if(piece[i][j]){
                    board[row+i][x_coordinate+j] = piece[i][j]; //parcayi boarda yerlestiriyoruz.
                }
            }
        }
        return 0; //parca basariyla yerlestirildi.

}

void shift_left(int piece[3][3]) {//eger oyun gercek zamanli olsaydi veya yeteri kadar if ile yapsaydim buna gerek kalmazdi , hard coding yapar isi bitirirdim.Hatta daha hizli da calisirdi-
//Basit bir tetris oyunu yapiyoruz hard-coding yapip gecebiliriz evet dogru daha da hizli calisir kod evet dogru ancak-
//Hard coding yapmayi tercih etmedim cunku esnek bir program, surdurulebilir bir program, bakim zorlugu olmayan bir program olmasi icin hard-coding yapilmamali--
//Yeteri sayida fazla if kullanip yapilir ancak, esnek ve bakimi kolay bir kod yapmak daha iyi bence. Bu yuzden hard-coding yapmak yerine-
//Dondurme algoritmasi ardindan da her parcayi sola yaslamayi tercih ettim. 3x3 matriste parca matrisimiz donunce 1 bulunan degerler hep en solda olmayabiliyor. Ancak bizim oyunumuzda-
//kullanici en sol parcayi yerlestirmek istedigi icin matrisi sola yasladim direkt. Parcanin en sol indexini tutarak o sekilde bir bakis acisiyla da yapilabilirdi ki oyle de dusundum-
//Ancak oyle de isler biraz uzuyordu. Bu sekilde tercih ettim.
    int i, j, min_column = 3;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (piece[i][j] == 1 && j < min_column) {
                min_column = j;
            }
        }
    }
    //Zaten parcalar donunce cogu muhtemelen yine en solda oldugundan buraya pek de girmiyor.
    if (min_column > 0) {
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (j + min_column < 3) {
                    piece[i][j] = piece[i][j + min_column];
                } else {
                    piece[i][j] = 0;
                }
            }
        }
    }
}

int play_game(){
    int pieces[10][3][3] = {{{1,1,1}, //Genelde matriste kullanilan parcalari ekledim.
                             {0,0,0},
                             {0,0,0}},{{1,0,0}, 
                                       {1,0,0},
                                       {1,0,0}},{{1,1,0},
                                                 {1,1,0},
                                                 {0,0,0}},{{1,0,0},
                                                           {1,0,0},
                                                           {0,0,0}},{{1,1,1},
                                                                     {0,1,0},
                                                                     {0,0,0}},{{1,0,0}, //BU L ile-
                                                                               {1,0,0},
                                                                               {1,1,0}},{{1,1,0}, //BU L aslinda birbirinden farkli.
                                                                                         {1,0,0},
                                                                                         {1,0,0}},{{0,1,1}, //BU S ile -   
                                                                                                   {1,1,0},
                                                                                                   {0,0,0}},{{1,1,0}, // BU S birbirinden farkli parca
                                                                                                             {0,1,1},
                                                                                                             {0,0,0}},{{1,0,0},
                                                                                                                       {0,0,0},
                                                                                                                       {0,0,0}}}; 

    int row,column,num1,num2;
    int **board;
    char decision;
    int score = 0;
    int controlx = 99;
    printf("To start the game, you must enter the game board size.(Number must be greater than 6)\n");
    do{
        
        printf("Enter the row number(must be greater than 6 and less than 100)\n");
        scanf("%d",&row);
        printf("Enter the column number.(must be greater than 6 and less than 100)\n");
        scanf("%d",&column);
        printf("\033[H\033[J");
    }while((row < 6) || (column < 6) || (row>100 || column >100)); //row ve column degerleri 6'dan kucuk olamaz.

    row = row+2; //Boardin cevresini kaplayacagim icin row ve columnlari 2 arttirmam gerek.
    column = column +2;
    board = create_board(row,column);
    row-=2;
    column-=2;
    srand(time(NULL));
    printf("\n\n");
    printf("To exit the game at any time, simply press the 'q' or 'Q' key.\n");
    
    do{
        int random_piece = rand() % 10;
        int temp_piece[3][3];
        copy_pieces(pieces[random_piece],temp_piece); 
        do{
            
            show_piece(temp_piece);
            printf("Your current score : $%d$\n",score);
            show_board(board,row+2,column+2);
            scanf(" %c",&decision);
            if(decision == 'r' || decision == 'R'){
                rotate_piece(temp_piece);
                shift_left(temp_piece);
                printf("Piece Rotated!!\n");
            }
            else if(decision == 'P' || decision == 'p'){
                do{
                    printf("Enter the X coordinate where you want to place the upper left corner of the piece:\n");
                    int x_coordinate;
                    scanf("%d",&x_coordinate);
                    controlx = check_place(temp_piece,board,row,row,column,x_coordinate);

                    if(controlx == 0){
                        printf("Piece placed at the desired location.\n");
                        remove_rows_if_full(board,row,column,&score);
                    }
                    else{
                        printf("Can not put here.\n");
                    }
                    
                }while(controlx == -1 && controlx != -11);
            }
            
            else{
                printf("Invalid choice.\n");
            }
        }while((decision != 'P' && decision != 'p') && (decision != 'Q' && decision != 'q'));
    }while((decision != 'Q' && decision != 'q') && (controlx != -11));
    printf("\033[2J\033[H");
    free_board(board,row+2);
    if(controlx == -11){
        game_over_message();
    }
    else{
        printf("\nExiting the game and transferring to the menu.\n");
    }
    return score;
    
}