


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
const int MAX_LENGTH = 1024; // The max length of any user input.

void inputStringFromUser(char *prompt, char *s, int arraySize); 
void songNameDuplicate(char *songName); 
void songNameFound(char *songName); 
void songNameNotFound(char *songName);
void songNameDeleted(char *songName); 
void artistFound(char *artist);
void artistNotFound(char *artist); 
void printMusicLibraryEmpty(void); /
void printMusicLibraryTitle(void); 
void printMusicLibraryList(Node *head); 
void searchForSong(Node *head, char songIntededToBeFound[MAX_LENGTH]); /
bool songAlreadyInPlaylist(Node *head, char songIntededToBeFound[MAX_LENGTH]); 

Node *insertANewNodeInOrder(Node *head, char songName[MAX_LENGTH], char artist[MAX_LENGTH], char genre[MAX_LENGTH]); 
Node *deleteTheSong(Node *head, char songIntededToBeDeleted[MAX_LENGTH]); 
Node *deleteAllNodesFromLibrary(Node *head); 

int main(void) 
{
    // Declare the head of the linked list.
    Node *head = NULL;
    
    char *songName, *artist, *genre;
    
    artist = (char *) malloc(MAX_LENGTH * sizeof (char));
    genre = (char *) malloc(MAX_LENGTH * sizeof (char));
    songName = (char*) malloc(MAX_LENGTH * sizeof (char));
    
    // Announce at the start of the program
    printf("Personal Music Library.\n\n");
    printf("%s", "Commands are I (insert), D (delete), S (search by song name),\n"
           "P (print), Q (quit).\n");

    char response;
    
    char input[MAX_LENGTH + 1];
    
    do 
    {
        inputStringFromUser("\nCommand", input, MAX_LENGTH); 
        response = toupper(input[0]); // Convert to uppercase to simplify later comparisons.

        if (response == 'I') 
        {
            char *promptName = "Song name";
            char *promptArtist = "Artist";
            char *promptGenre = "Genre";

            inputStringFromUser(promptName, songName, MAX_LENGTH);
            inputStringFromUser(promptArtist, artist, MAX_LENGTH);
            inputStringFromUser(promptGenre, genre, MAX_LENGTH);
            
            if (!songAlreadyInPlaylist(head, songName)) 
            {
                head = insertANewNodeInOrder(head, songName, artist, genre);
            } 
            
            else
            {
                songNameDuplicate(songName);
            }
        }
        
        else if (response == 'D') // Delete a song from the list.
        {
            char *prompt = "\nEnter the name of the song to be deleted";
            
            inputStringFromUser(prompt, songName, MAX_LENGTH);
            head = deleteTheSong(head, songName);
        }
        
        else if (response == 'S') // Search for a song by its name.
        {
            char *prompt = "\nEnter the name of the song to search for";

            inputStringFromUser(prompt, songName, MAX_LENGTH);
            searchForSong(head, songName);
        }
        
        else if (response == 'P') // Print the music library.
        {
            printMusicLibraryList(head);
        }
        
        else if (response == 'Q') // do nothing, we'll catch this below
        {
            ; 
        }
        
        else // do this if no command matched ...
        {
            printf ("\nInvalid command.\n");
        }
        
    } while (response != 'Q'); // Delete the entire linked list.

    head = deleteAllNodesFromLibrary(head);
    printMusicLibraryList(head); 

    return 0;
}


void inputStringFromUser(char *prompt, char *s, int maxStrLength) 
{
    int i = 0;
    char c;

    printf("%s --> ", prompt);
    while (i < maxStrLength && (c = getchar()) != '\n')
        s[i++] = c;
    s[i] = '\0';
}


void songNameDuplicate(char *songName) 
{
    printf("\nA song with the name '%s' is already in the music library.\n"
           "No new song entered.\n", songName);
}


void songNameFound(char *songName) 
{
    printf("\nThe song name '%s' was found in the music library.\n\n", songName);
}


void songNameNotFound(char *songName) 
{
    printf("\nThe song name '%s' was not found in the music library.\n", songName);
}

void songNameDeleted(char *songName) 
{
    printf("\nDeleting a song with name '%s' from the music library.\n", songName);
}

void printMusicLibraryEmpty(void) {
    printf("\nThe music library is empty.\n");
}

void printMusicLibraryTitle(void) 
{
    printf("\nMy Personal Music Library: \n");
}

void printMusicLibraryList(Node *head) 
{
    Node *current = head;
    
    if (current == NULL)
    {
        printMusicLibraryEmpty();
    }
    
    else 
    {
        printMusicLibraryTitle();
        
        while (current != NULL)
        {
            printf("\n");
            printf("%s\n", current -> songName);
            printf("%s\n", current -> artist);
            printf("%s\n", current -> genre);
            current = current -> linkToNextNode;
        }
    }
}

// This function searches the linked list for a given song name and then either prints the appropriate song or, if a node is not found, prints an error message (S command)
void searchForSong(Node *head, char songIntededToBeFound[MAX_LENGTH]) 
{
    if (head == NULL)
    {
        return;
    }
    
    Node *current = head;
    
    while (current != NULL) 
    {
        if (strcmp(current -> songName, songIntededToBeFound) == 0) 
        {
            songNameFound(songIntededToBeFound);
            printf("%s\n", current -> songName);
            printf("%s\n", current -> artist);
            printf("%s\n", current -> genre);
            return;
        }
        current = current -> linkToNextNode;
    }
    
    songNameNotFound(songIntededToBeFound);
    return;
}

// This function checks if the song is already in the playlist.
bool songAlreadyInPlaylist(Node *head, char songIntededToBeFound[MAX_LENGTH])
{
    if (head == NULL)
    {
        return false;
    }   
    
    Node *current = head;
    while (current != NULL) 
    {
        if (strcmp(current->songName, songIntededToBeFound) == 0)
        {
            return true;
        }
        
        current = current -> linkToNextNode;
    }
    
    return false;
}

// This is the function for inserting a new node (the I command) into the linked list.
Node *insertANewNodeInOrder(Node *head, char songName[MAX_LENGTH], char artist[MAX_LENGTH], char genre[MAX_LENGTH]) 
{
    Node *linkToNextNode = head;
    if (head == NULL || strcmp(head -> songName, songName) > 0) 
    {
        Node *insert = (Node *) malloc( sizeof(Node));
    
        insert -> songName = (char *) malloc(MAX_LENGTH * sizeof(char));
        insert -> artist = (char *) malloc(MAX_LENGTH * sizeof(char));
        insert -> genre = (char *) malloc(MAX_LENGTH * sizeof(char));
    
        if (insert != NULL) 
        {
            strcpy(insert -> songName, songName);
            strcpy(insert -> artist, artist);
            strcpy(insert -> genre, genre);
            insert -> linkToNextNode = linkToNextNode;
        }
    
        return insert;
    }
    
    Node *current = head;
    
    while (current -> linkToNextNode != NULL && strcmp(current -> linkToNextNode -> songName, songName) < 0) 
    {
        current = current -> linkToNextNode;
    }
    
    Node *insert = (Node *) malloc(sizeof (Node));
    
    insert -> songName = (char *) malloc(MAX_LENGTH * sizeof (char));
    insert -> artist = (char *) malloc(MAX_LENGTH * sizeof (char));
    insert -> genre = (char *) malloc(MAX_LENGTH * sizeof (char));
    
    if (insert != NULL) 
    {
        strcpy(insert -> songName, songName);
        strcpy(insert -> artist, artist);
        strcpy(insert -> genre, genre);
        insert -> linkToNextNode = linkToNextNode;
    }
    
    current -> linkToNextNode = insert;
    
    return head;
}

// This function is for deleting a song from the personal music library.
Node *deleteTheSong(Node *head, char songIntendedToBeDeleted[MAX_LENGTH]) 
{
    if (head == NULL)
    {
        return NULL;
    }
    
    // If the first node is to be deleted
    if (strcmp(head -> songName, songIntendedToBeDeleted) == 0) 
    {
        Node *secondNode = head -> linkToNextNode;
        songNameDeleted(head -> songName);
        free(head -> songName);
        free(head -> artist);
        free(head -> genre);
        free(head); 
        return secondNode;
    }
    
    bool foundTheSong = false;
    
    Node *current = head;
    
    while (!foundTheSong && current -> linkToNextNode != NULL) 
    {
        if (strcmp(current -> linkToNextNode -> songName, songIntendedToBeDeleted) == 0)
        {
            foundTheSong = true;
        }
        
        else
        {
            current = current -> linkToNextNode;
        }
    }
    
    // if there exists a node to be deleted
    if (current -> linkToNextNode != NULL) 
    {
        Node *songToRemove = current -> linkToNextNode;
        current -> linkToNextNode = current -> linkToNextNode -> linkToNextNode;
        songNameDeleted(songToRemove -> songName);
        free(songToRemove -> songName);
        free(songToRemove -> artist);
        free(songToRemove -> genre);
        free(songToRemove); 
    }
    
    return head;
}

// This function is for executing when the Q command is entered.
Node *deleteAllNodesFromLibrary(Node *head) 
{
    if (head == NULL)
    {
        return head;
    }
    
    while (head != NULL) 
    {
        Node *firstNode = head;
        head = head -> linkToNextNode;
        songNameDeleted(firstNode -> songName);
        free(firstNode -> songName);
        free(firstNode -> artist);
        free(firstNode -> genre);
        free(firstNode); 
    }

    return head;
}
