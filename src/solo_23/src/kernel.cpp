// The memory related functions in this file are based on Per-Arne Andersen's implementation found at https://perara.notion.site/IKT218-Advanced-Operating-Systems-2024-bfa639380abd46389b5d69dcffda597a

extern "C" {
    #include <libc/stdio.h>
    #include <libc/string.h>
    #include <memory.h>
    #include <isr.h>
    #include <io.h>
    #include <libc/stdio.h>
    #include <keyboard.h>
    #include <pit.h>
    #include <song.h>
    #include <frequencies.h>
    
    int kernel_main(void);
}


// Existing global operator new overloads
void* operator new(size_t size) {
    return malloc(size);
}

void* operator new[](size_t size) {
    return malloc(size);
}

// Existing global operator delete overloads
void operator delete(void* ptr) noexcept {
    free(ptr);
}

void operator delete[](void* ptr) noexcept {
    free(ptr);
}

// Add sized-deallocation functions
void operator delete(void* ptr, size_t size) noexcept {
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}

void operator delete[](void* ptr, size_t size) noexcept {
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}

SongPlayer* create_song_player() {
    auto* player = new SongPlayer();
    player->play_song = play_song_impl;
    return player;
}

int get_user_choice();

int kernel_main(){
    clrscr();
    printf("Starting kernel initialization");

    for (int i = 0; i < 3; i++){
        putc('.');
        sleep_interrupt(50);
    }

    printf("\nInitializing GDT");

    for (int i = 0; i < 10; i++){
        putc('.');
        sleep_interrupt(50);
    }

    printf("\nRemapping PIC");

    for (int i = 0; i < 13; i++){
        putc('.');
        sleep_interrupt(50);
    }

    printf("\nInitializing IDT");

    for (int i = 0; i < 10; i++){
        putc('.');
        sleep_interrupt(50);
    }

    printf("\nInitializing ISR");

    for (int i = 0; i < 10; i++){
        putc('.');
        sleep_interrupt(50);
    }

    printf("\nEnabling PIT interrupt");

    for (int i = 0; i < 4; i++){
        putc('.');
        sleep_interrupt(50);
    }

    printf("\nEnabling keyboard interrupt");

    for (int i = 0; i < 3; i++){
        putc('.');
        sleep_interrupt(50);
    }

    printf("\nInitializing kernel memory");

    for (int i = 0; i < 4; i++){
        putc('.');
        sleep_interrupt(50);
    }

    printf("\nInitializing  paging");

    for (int i = 0; i < 10; i++){
        putc('.');
        sleep_interrupt(50);
    }

    printf("\nSystem initialization complete.");

    printf("\nprinting memory layout");

    for (int i = 0; i < 10; i++){
        putc('.');
        sleep_interrupt(100);
    }

    printf("\n");

    print_memory_layout();  

    printf("\nLoading Kernel.");

    for (int i = 0; i < 20; i++){
        putc('.');
        sleep_interrupt(100);
    }
    
    clrscr();

    for (int i = 0; i < 60; i++){
        putc('*');
        sleep_interrupt(25);
    }

    printf("\n    W     W     aaaa    eeeee   LLL         OOO     SSSS  \n"); 
    printf("    W     W    a    a   e       LLL        O   O   S      \n"); 
    printf("    W  W  W    aaaaaa   eeee    LLL        O   O    SSS   \n"); 
    printf("    W W W W    a    a   e       LLL        O   O       S  \n"); 
    printf("     W   W     a    a   eeeee   LLLLLL      OOO    SSSS   \n"); 

    for (int i = 0; i < 60; i++){
        putc('*');
        sleep_interrupt(5);
    }

    printf("\n");


    clrscr();

    Song* songs[] = {

        new Song({Lamma_Bada_Yatathanna, sizeof(Lamma_Bada_Yatathanna) / sizeof(Note)}),

        new Song({Happy_Birthday, sizeof(Happy_Birthday) / sizeof(Note)}),

        new Song({starwars_theme, sizeof(starwars_theme) / sizeof(Note)}),

        new Song({music_4, sizeof(music_4) / sizeof(Note)}),

    };
    uint32_t n_songs = sizeof(songs) / sizeof(Song*);

    // Create a song player and play each song
    SongPlayer* player = create_song_player();

    // Play Lamma Bada Yatathanna
    printf("Playing Lamma Bada Yatathanna...\n");
    player->play_song(songs[0]);
    printf("Finished playing Lamma Bada Yatathanna.\n");

    for (int i = 0; i < 40; i++){
        putc('*');
        sleep_interrupt(20);
    }

    // Play The Final Countdown
    printf("\nPlaying Happy Birthday to You...\n");
    player->play_song(songs[1]);
    printf("Finished playing Happy Birthday to You.\n");

    for (int i = 0; i < 40; i++){
        putc('*');
        sleep_interrupt(20);
    }

    // Play Star Wars Theme
    printf("\nPlaying Star Wars Theme...\n");
    player->play_song(songs[2]);
    printf("Finished playing Star Wars Theme.\n");

    for (int i = 0; i < 40; i++){
        putc('*');
        sleep_interrupt(20);
    }

    // Play music_4
    printf("\nPlaying Music 4...\n");
    player->play_song(songs[3]);
    printf("Finished playing Music 4.\n");

    clrscr();

    printf("wael_os> ");

    while(true);
}

