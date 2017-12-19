#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>      //Printf
#include <stdint.h> 

//Defines internos necesarios
#define HEIGHT_DIS 400
#define WIDTH_DIS 400
#define WIDTH_SYMS_O 100
#define WIDTH_SYMS 50
#define WIDTH_SYMS_R 50
#define HEIGHT_SYMS_O 50
#define HEIGHT_SYMS 100
#define HEIGHT_SYMS_R 50
#define COL1 75
#define FINCOL1 (COL1 + WIDTH_SYMS)
#define COL2 (FINCOL1 + 50)
#define FINCOL2_O (COL2 + WIDTH_SYMS_O)
#define FINCOL2 (COL2 + WIDTH_SYMS)

//Para trabajar en el arreglo
#define TAMCOLAEVENTO 100
enum {PLAY, RESTART, MENU, SETTINGS, MAX_SCORE, QUIT, RULES};

//Necesario para debug
#define DEBUG 1


#define false 0
#define true 1

char cola_ev[TAMCOLAEVENTO];        //Cola de eventos
char* pevento = cola_ev; //PUNTERO EN DONDE SE AGREGAN LOS EVENTOS


int main(void) 
{
     //variables necesarias para allegro
	ALLEGRO_DISPLAY * display = NULL;       //Creo display
	ALLEGRO_BITMAP * display_background;    //Fondo
	ALLEGRO_BITMAP * play;                  //Boton play
	ALLEGRO_BITMAP * restart;               //boton restart
	ALLEGRO_BITMAP * settings;              //bton settings
	ALLEGRO_BITMAP * menu;                  //Boton menu
	ALLEGRO_BITMAP * quit;                  //bton quit
	ALLEGRO_BITMAP * tetris;                //titulo
	ALLEGRO_BITMAP * max_score;             //boton max score
	ALLEGRO_BITMAP * rules;                 //boton rules
	ALLEGRO_BITMAP * on;                 //boton epilepsia on
	ALLEGRO_BITMAP * off;                 //boton epilepsia off
	ALLEGRO_BITMAP * uno;                 //boton dif 1
	ALLEGRO_BITMAP * dos;                 //boton dif 2
	ALLEGRO_BITMAP *tres;                 //boton dif 3
        ALLEGRO_EVENT_QUEUE  * event_queue = NULL;   //creo cola de eventos
        
        char close_display = false;             //Variable para ver si cerrar el display
        char epilepsia = false; //Por default empieza apagado
        char dificultad = 1; //Por default empieza en facil (1)
     //Inicializo Allegro
	if( !al_init() ) //lo mismo que igual a 0
	{
		fprintf(stderr, "Unable to start allegro\n");
		return -1;
	}
        
        
        //Inicializo cola de eventos
        event_queue = al_create_event_queue();
        if(!event_queue) 
        {
            al_uninstall_system();
            printf("failed to create event_queue!\n");
            return -1;
        }
    
        //Inicializo teclado
        if(!al_install_keyboard()) 
        {
            printf("failed to initialize the keyboard!\n");
            al_destroy_event_queue(event_queue);
            al_uninstall_system();
            return -1;
        }
        
         //Inicializo Mouse
    
        if (!al_install_mouse())
        {
            printf ("failed to inicialize mouse!\n");
            al_destroy_event_queue(event_queue);
            al_uninstall_system();
            return -1;
        }
        
        
        //Inicializo configuracion de imagenes
	else if( !al_init_image_addon())
	{
		fprintf(stderr,"Unable to start image addon \n"); //Igual que printf pero imprime al error std 
		al_uninstall_system();
                al_destroy_event_queue(event_queue);
		return -1;
	}
        
       //Cargo bitmaps
        
        //Cargo fondo
	else if( !(display_background = al_load_bitmap("Setting.jpg")) )
	{
		fprintf(stderr,"Unable to load background\n"); 
		al_uninstall_system();
		al_shutdown_image_addon();
                al_destroy_event_queue(event_queue);
		return -1;
	}
        //Cargo off
        else if( !(off = al_load_bitmap("off.jpg")) )
	{
		fprintf(stderr,"Unable to load background\n"); 
		al_destroy_bitmap(display_background);
		al_shutdown_image_addon();
                al_destroy_event_queue(event_queue);
		return -1;
	}
        
        //Cargo on
        else if( !(on = al_load_bitmap("on.jpg")) )
	{
		fprintf(stderr,"Unable to load background\n"); 
		al_destroy_bitmap(display_background);
		al_destroy_bitmap(off);
		al_shutdown_image_addon();
                al_destroy_event_queue(event_queue);
		return -1;
	}
        
        //Cargo uno
        else if( !(uno = al_load_bitmap("uno.jpg")) )
	{
		fprintf(stderr,"Unable to load uno\n"); 
		al_destroy_bitmap(display_background);
		al_destroy_bitmap(off);
		al_destroy_bitmap(on);
		al_shutdown_image_addon();
                al_destroy_event_queue(event_queue);
		return -1;
	}
        
        //Cargo  dos
        else if( !(dos = al_load_bitmap("dos.jpg")) )
	{
		fprintf(stderr,"Unable to load dos\n"); 
		al_destroy_bitmap(display_background);
		al_destroy_bitmap(off);
		al_destroy_bitmap(uno);
		al_destroy_bitmap(on);
		al_shutdown_image_addon();
                al_destroy_event_queue(event_queue);
		return -1;
	}
        
        //Cargo tres
        else if( !(tres = al_load_bitmap("tres.jpg")) )
	{
		fprintf(stderr,"Unable to load uno\n"); 
		al_destroy_bitmap(display_background);
		al_destroy_bitmap(off);
		al_destroy_bitmap(on);
		al_destroy_bitmap(uno);
		al_destroy_bitmap(dos);
		al_shutdown_image_addon();
                al_destroy_event_queue(event_queue);
		return -1;
	}
        
    /*    //cargo boton play
	else if( !(play = al_load_bitmap("play.png")) ) 
	{
		fprintf(stderr,"Unable to load play\n"); 
                al_destroy_bitmap(display_background);
		al_uninstall_system();
		al_shutdown_image_addon();
                al_destroy_event_queue(event_queue);
		return -1;
	}
        //Cargo quit
        else if( !(quit = al_load_bitmap("quit.png")) ) 
	{
		fprintf(stderr,"Unable to load quit\n"); 
                al_destroy_bitmap(display_background);
                al_destroy_bitmap(play);
		al_uninstall_system();
		al_shutdown_image_addon();
                al_destroy_event_queue(event_queue);
		return -1;
	}*/
        //cargo restart
        else if( !(restart = al_load_bitmap("restart.png")) ) 
	{
		fprintf(stderr,"Unable to load restart\n"); 
                al_destroy_bitmap(display_background);
                al_destroy_bitmap(uno);
                al_destroy_bitmap(dos);
                al_destroy_bitmap(tres);
                al_destroy_bitmap(on);
                al_destroy_bitmap(off);
		al_shutdown_image_addon();
                al_destroy_event_queue(event_queue);
		return -1;
	}
 /*       //Cargo max_score
        else if( !(max_score = al_load_bitmap("maxscore.png")) ) 
	{
		fprintf(stderr,"Unable to load max score\n"); 
                al_destroy_bitmap(display_background);
                al_destroy_bitmap(play);
                al_destroy_bitmap(quit);
                al_destroy_bitmap(restart);
		al_uninstall_system();
		al_shutdown_image_addon();
                al_destroy_event_queue(event_queue);
		return -1;
	}
        //Cargo rules
        else if( !(rules = al_load_bitmap("rules.png")) ) 
	{
		fprintf(stderr,"Unable to load rules\n"); 
                al_destroy_bitmap(display_background);
                al_destroy_bitmap(play);
                al_destroy_bitmap(quit);
                al_destroy_bitmap(restart);
                al_destroy_bitmap(max_score);
		al_uninstall_system();
		al_shutdown_image_addon();
                al_destroy_event_queue(event_queue);
		return -1;
	}
        //cargo settings
        else if( !(settings = al_load_bitmap("settings.png")) ) 
	{
		fprintf(stderr,"Unable to load settings\n"); 
                al_destroy_bitmap(display_background);
                al_destroy_bitmap(rules);
                al_destroy_bitmap(play);
                al_destroy_bitmap(quit);
                al_destroy_bitmap(restart);
                al_destroy_bitmap(max_score);
		al_uninstall_system();
		al_shutdown_image_addon();
                al_destroy_event_queue(event_queue);
		return -1;
	}
        //Cargo menu
        else if( !(menu = al_load_bitmap("menu.png")) ) 
	{
		fprintf(stderr,"Unable to load menu\n"); 
                al_destroy_bitmap(display_background);
                al_destroy_bitmap(rules);
                al_destroy_bitmap(play);
                al_destroy_bitmap(quit);
                al_destroy_bitmap(restart);
                al_destroy_bitmap(max_score);
                al_destroy_bitmap(settings);
		al_uninstall_system();
		al_shutdown_image_addon();
                al_destroy_event_queue(event_queue);
		return -1;
	}
        
        //Cargo tetris
	else if( !(tetris = al_load_bitmap("Tetris.png")) )
	{
		fprintf(stderr,"Unable to load tetris\n"); 
                al_destroy_bitmap(display_background);
                al_destroy_bitmap(rules);
                al_destroy_bitmap(play);
                al_destroy_bitmap(quit);
                al_destroy_bitmap(restart);
                al_destroy_bitmap(max_score);
                al_destroy_bitmap(settings);
                al_destroy_bitmap(menu);
		al_uninstall_system();
		al_shutdown_image_addon();
                al_destroy_event_queue(event_queue);
		return -1;
	}*/
        
        //Inicializo display
	else if( !(display = al_create_display(WIDTH_DIS,HEIGHT_DIS)) )
	{
		fprintf(stderr,"Unable to create display\n"); 
		al_destroy_bitmap(display_background);
                al_destroy_bitmap(on);
                al_destroy_bitmap(off);
                al_destroy_bitmap(uno);
                al_destroy_bitmap(restart);
                al_destroy_bitmap(dos);
                al_destroy_bitmap(tres);
		al_uninstall_system();
		al_shutdown_image_addon();
                al_destroy_event_queue(event_queue);
		return -1;
	}
       
        
        //Incluyo los eventos a la cola de eventos
        al_register_event_source(event_queue, al_get_display_event_source(display));
        al_register_event_source(event_queue, al_get_keyboard_event_source());
        al_register_event_source(event_queue, al_get_mouse_event_source());
	
	//Dibujo en el display
        
        al_clear_to_color(al_map_rgb(0,0,0));   //pongo el fondo real en negro
        
	//Agrego una imagen para hacer el fondo del menu
        al_draw_scaled_bitmap(display_background,
						0,0, al_get_bitmap_width(display_background),al_get_bitmap_height(display_background), //imagen
						0,0,al_get_display_width(display),al_get_display_height(display), //a que tamaño queres que se dibuje la imagen
						0); //SIn flags podrian usar ALLEGRO_FLIP_HORIZONTAL o ALLEGRO_FLIP_VERTICAL muy utiles
        
        //Agrego off por default para epilepsia
        //Agrego boton off
        al_draw_scaled_bitmap(off,
            0,0, al_get_bitmap_width(off),al_get_bitmap_height(off),
            COL2,HEIGHT_SYMS_O*6 +10 ,WIDTH_SYMS_O,HEIGHT_SYMS_O,  // POSICION. tamano que quiero que se imprima la imagen
            0); //rotacion*/
        
        //Agrego boton uno
        al_draw_scaled_bitmap(uno,
            0,0, al_get_bitmap_width(uno),al_get_bitmap_height(uno),
            COL2,HEIGHT_SYMS*2 -20 ,WIDTH_SYMS,HEIGHT_SYMS,  // POSICION. tamano que quiero que se imprima la imagen
            0); //rotacion*/
        //Agrego boton DOS
        al_draw_scaled_bitmap(dos,
            0,0, al_get_bitmap_width(dos),al_get_bitmap_height(dos),
            FINCOL2 + 20,HEIGHT_SYMS*2 -20 ,WIDTH_SYMS,HEIGHT_SYMS,  // POSICION. tamano que quiero que se imprima la imagen
            0); //rotacion*/
        //Agrego boton tres
        al_draw_scaled_bitmap(tres,
            0,0, al_get_bitmap_width(tres),al_get_bitmap_height(tres),
            FINCOL2 + 2*22 + WIDTH_SYMS,HEIGHT_SYMS*2 -20 ,WIDTH_SYMS,HEIGHT_SYMS,  // POSICION. tamano que quiero que se imprima la imagen
            0); //rotacion*/
        
/*       //Agrego tetris
        al_draw_scaled_bitmap(tetris,
						0,0, al_get_bitmap_width(tetris),al_get_bitmap_height(tetris), //imagen
						100,0,200,100, //a que tamaño queres que se dibuje la imagen
						0); //SIn flags podrian usar ALLEGRO_FLIP_HORIZONTAL o ALLEGRO_FLIP_VERTICAL muy utiles
        //Agrego boton play
        al_draw_scaled_bitmap(play,
            0,0, al_get_bitmap_width(play),al_get_bitmap_height(play),
            COL1,HEIGHT_SYMS ,WIDTH_SYMS,HEIGHT_SYMS,  // POSICION. tamano que quiero que se imprima la imagen
            0); //rotacion*/
 /*      //Agrego boton restart
        al_draw_scaled_bitmap(restart,
            0,0, al_get_bitmap_width(restart),al_get_bitmap_height(restart),
            COL2,HEIGHT_SYMS ,WIDTH_SYMS,HEIGHT_SYMS,  // POSICION. tamano que quiero que se imprima la imagen
            0); //rotacion*/

        //Agrego boton volver al menu ppal
        al_draw_scaled_bitmap(restart,
            0,0, al_get_bitmap_width(restart),al_get_bitmap_height(restart),
            0,0,WIDTH_SYMS_R,HEIGHT_SYMS_R,  // POSICION. tamano que quiero que se imprima la imagen
            0); //rotacion
        
  /*      //Agrego boton menu
        al_draw_scaled_bitmap(menu,
            0,0, al_get_bitmap_width(menu),al_get_bitmap_height(menu),
            COL2,HEIGHT_SYMS*2 + 50 ,WIDTH_SYMS,HEIGHT_SYMS,  // POSICION. tamano que quiero que se imprima la imagen
            0); //rotacion*/

	al_flip_display();
        
        while (!close_display)
        {
            ALLEGRO_EVENT evento;   //Creo variable para menejar eventos
            if (al_get_next_event(event_queue, &evento))
            {
                if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) //Verifico si cerrar el display
                    close_display = true;
                if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                {
                    /*if ((evento.mouse.x >= COL1) && (evento.mouse.x <= FINCOL1) )   //Estoy en la primer columna
                    {   
                        //Boton play, debe volver al estado jugando, limpiando la cola de eventos anteriores
                        //Pero el estado de la matriz de juego sigue igual
                        //Tambien debo cerrar el display del menu de pausa
                        if ((evento.mouse.y >= HEIGHT_SYMS) && (evento.mouse.y <= HEIGHT_SYMS*2))
                        {
                           *pevento++ = PLAY; //Pongo en el arreglo que tocaron el boton play y corro el puntero
                           
                           #if DEBUG
                            printf("boton play\n");
                            #endif
                        }
                        //Boton quit
                        //Se debe terminar el programa
                        if ((evento.mouse.y >= (HEIGHT_SYMS*2 + 50)) && (evento.mouse.y <= ((HEIGHT_SYMS*2 + 50) + HEIGHT_SYMS)))
                        {
                            *pevento++ = QUIT;

                            close_display = true;   //Se cierra el frontend
                            #if DEBUG
                            printf("boton quit\n");
                            #endif
                        }
                          
                    }*/
                    
                    if ((evento.mouse.x >= COL2) && (evento.mouse.x <= FINCOL2_O) )   //Estoy en la segunda columna
                    {
                        //Boton epilepsia
                        
                        if ((evento.mouse.y >= (HEIGHT_SYMS_O*6 +10)) && (evento.mouse.y <= (HEIGHT_SYMS_O*6 +10)+ HEIGHT_SYMS_O))
                        {
                            if (epilepsia == true)
                            {
                            al_draw_scaled_bitmap(off,
            0,0, al_get_bitmap_width(off),al_get_bitmap_height(off),
            COL2,HEIGHT_SYMS_O*6 +10 ,WIDTH_SYMS_O,HEIGHT_SYMS_O,  // POSICION. tamano que quiero que se imprima la imagen
            0); //rotacion*/
                            al_flip_display();
                            epilepsia = false;
                            
                            #if DEBUG
                            printf("epilepsia off\n");
                            #endif
                            }
                            else if (epilepsia == false)
                            {
                              al_draw_scaled_bitmap(on,
            0,0, al_get_bitmap_width(on),al_get_bitmap_height(on),
            COL2,HEIGHT_SYMS_O*6 +10 ,WIDTH_SYMS_O,HEIGHT_SYMS_O,  // POSICION. tamano que quiero que se imprima la imagen
            0); //rotacion*/
                            al_flip_display();  
                            epilepsia = true;
                            
                            #if DEBUG
                            printf("epilepsia on\n");
                            #endif
                            }
                           #if DEBUG
                            printf("boton epilepsia\n");
                            #endif
                        }
                        
                        
                    }
                    if ((evento.mouse.x >= COL2) && (evento.mouse.x <= FINCOL2) )   //Estoy en la segunda columna
                    {
                    //Boton uno
                        //se cierra este menu y se debe abrir el primero. Se cambia al estado menu ppal
                        if ((evento.mouse.y >= (HEIGHT_SYMS*2 -20)) && (evento.mouse.y <= ((HEIGHT_SYMS*2 -20) + HEIGHT_SYMS)))
                        {
                            dificultad = 1;
                            #if DEBUG
                            printf("boton 1\n");
                            #endif
                        }
                    }
                    
                    
                    //Boton 2
                    if ((evento.mouse.x >= FINCOL2 + 20) && (evento.mouse.x <= (FINCOL2 + 20) + WIDTH_SYMS) )   
                    {
                        if ((evento.mouse.y >= (HEIGHT_SYMS*2 -20)) && (evento.mouse.y <= (HEIGHT_SYMS*2 -20)+ HEIGHT_SYMS))
                        {
                            dificultad = 2;
                            #if DEBUG
                            printf("boton 2\n");
                            #endif
                        }
                    }
                    
                    
                    
                    //Boton return
                    if (WIDTH_SYMS_R)   
                    {
                        if (evento.mouse.y <=  HEIGHT_SYMS_R)
                        {
                            close_display = true;
                            *(pevento++) = menu;    //debo pasar al estado menu, paso el evento
                            #if DEBUG
                            printf("boton quit\n");
                            #endif
                        }
                    }
                }
            }
            
            
	
	
	

	
        }
        
        al_destroy_bitmap(display_background);
        al_destroy_bitmap(off);
        al_destroy_bitmap(on);
	al_shutdown_image_addon();
        al_destroy_event_queue(event_queue);
        al_destroy_display(display);
        al_destroy_bitmap(uno);
        al_destroy_bitmap(dos);
        al_destroy_bitmap(tres);
        al_destroy_bitmap(restart);
        return 0;
}


