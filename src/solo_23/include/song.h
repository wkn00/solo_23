#ifndef SONG_H
#define SONG_H

#include "frequencies.h"
#include "io.h"

// Define a struct to represent a single musical note
typedef struct {
    uint32_t frequency; // The frequency of the note in Hz (e.g., A4 = 440 Hz)
    uint32_t duration;  // The duration of the note in milliseconds
} Note;

// Define a struct to represent a song
typedef struct {
    Note* notes;        // Pointer to an array of Note structs representing the song
    uint32_t length;    // The number of notes in the song
} Song;

// Define a struct to represent a song player
typedef struct {
    void (*play_song)(Song* song); // Function pointer to a function that plays a song
} SongPlayer;

// Function prototype for creating a new SongPlayer instance
// Returns a pointer to a newly created SongPlayer object
SongPlayer* create_song_player();
void play_song_impl(Song *song) ;


static Note Lamma_Bada_Yatathanna[] = {
    {D5, 500}, {E5, 250}, {F5, 250}, {G5, 500}, // Initial ascending phrase
    {A4, 250}, {G5, 250}, {F5, 250}, {E5, 250}, // First descending phrase
    {D5, 500}, {R, 250}, {G5, 250}, {F5, 500}, // Variation with pause
    {E5, 500}, {D5, 250}, {C5, 250}, {D5, 1000}, // Closing phrase of first section
    
    {D5, 500}, {E5, 250}, {F5, 250}, {G5, 500}, // Repeat initial phrase
    {A4, 250}, {G5, 250}, {F5, 250}, {E5, 250}, // Repeat descending
    {F5, 500}, {E5, 250}, {D5, 250}, {C5, 500}, // New descending phrase
    {D5, 250}, {E5, 250}, {F5, 250}, {G5, 500}, // Ascend again
    
    {A4, 250}, {G5, 250}, {F5, 250}, {E5, 250}, // Descend once more
    {D5, 500}, {R, 250}, {G5, 250}, {F5, 500}, // Variation with pause
    {E5, 500}, {D5, 250}, {C5, 250}, {D5, 1000}, // Closing phrase
    {D5, 500}, {E5, 250}, {F5, 250}, {G5, 500}, // Recap initial theme
    
    {A4, 250}, {G5, 250}, {F5, 250}, {E5, 500}, // Extended descending
    {F5, 500}, {E5, 500}, {D5, 500}, {C5, 1000}, // Extended final descent and hold
    // Repeat the whole structure or part of it for a complete performance
    {D5, 500}, {E5, 250}, {F5, 250}, {G5, 500}, // Initial ascending phrase
    {A4, 250}, {G5, 250}, {F5, 250}, {E5, 250}, // First descending phrase
    {D5, 500}, {R, 250}, {G5, 250}, {F5, 500}, // Variation with pause
    {E5, 500}, {D5, 250}, {C5, 250}, {D5, 1000}, // Closing phrase of first section
    
    {D5, 500}, {E5, 250}, {F5, 250}, {G5, 500}, // Repeat initial phrase
    {A4, 250}, {G5, 250}, {F5, 250}, {E5, 250}, // Repeat descending
    {F5, 500}, {E5, 250}, {D5, 250}, {C5, 500}, // New descending phrase
    {D5, 250}, {E5, 250}, {F5, 250}, {G5, 500}, // Ascend again
    
    {A4, 250}, {G5, 250}, {F5, 250}, {E5, 250}, // Descend once more
    {D5, 500}, {R, 250}, {G5, 250}, {F5, 500}, // Variation with pause
    {E5, 500}, {D5, 250}, {C5, 250}, {D5, 1000}, // Closing phrase
    {D5, 500}, {E5, 250}, {F5, 250}, {G5, 500}, // Recap initial theme
    
    {A4, 250}, {G5, 250}, {F5, 250}, {E5, 500}, // Extended descending
    {F5, 500}, {E5, 500}, {D5, 500}, {C5, 1000} // Extended final descent and hold
    // The final repeat concludes the full performance
};


static Note Happy_Birthday[] = {
    {G4, 500}, {G4, 500}, {A4, 1000}, {G4, 1000}, {C5, 1000}, {B4, 2000}, // "Happy Birthday to You"
    {G4, 500}, {G4, 500}, {A4, 1000}, {G4, 1000}, {D5, 1000}, {C5, 2000}, // "Happy Birthday to You"
    {G4, 500}, {G4, 500}, {G5, 1000}, {E5, 1000}, {C5, 1000}, {B4, 1000}, {A4, 2000}, // "Happy Birthday Dear [Name]"
    {F5, 500}, {F5, 500}, {E5, 1000}, {C5, 1000}, {D5, 1000}, {C5, 2000}  // "Happy Birthday to You"
};


static Note starwars_theme[] = {
    // Opening phrase
    {A4, 500}, {A4, 500}, {A4, 500}, 
    {F4, 375}, {C5, 125}, 
    {A4, 500}, {F4, 375}, {C5, 125}, {A4, 1000}, 
    {E5, 500}, {E5, 500}, {E5, 500}, 
    {F5, 375}, {C5, 125},
    
    // Next phrase
    {G4, 500}, {F4, 375}, {C5, 125}, {A4, 1000}, 
    {A5, 500}, {A4, 375}, {A4, 125}, 
    {A5, 500}, {G5, 375}, {F5, 125}, {E5, 125}, {D5, 125}, 
    {C5, 250}, {B4, 250}, {A4, 500},

    // End note
    {R, 500}
};

static Note music_4[] = {
    {C4, 500}, {D4, 500}, {E4, 500}, {C4, 500},
    {C4, 500}, {D4, 500}, {E4, 500}, {C4, 500},
    {E4, 500}, {F4, 500}, {G4, 1000},
    {E4, 500}, {F4, 500}, {G4, 1000},
    {G4, 250}, {A4, 250}, {G4, 250}, {F4, 250}, {E4, 500}, {C4, 500},
    {G4, 250}, {A4, 250}, {G4, 250}, {F4, 250}, {E4, 500}, {C4, 500},
    {C4, 500}, {G3, 500}, {C4, 1000},
    {C4, 500}, {G3, 500}, {C4, 1000}
};


#endif
