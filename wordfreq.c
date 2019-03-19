#include "wordfreqq.h"

//function to create a Word node. Return the pointer to the node created, NULL otherwise
Word *initializeWord()
{
  Word *w = (Word *)(malloc(sizeof(Word)));
  if (w != NULL) //if space is avaiable
  {
    w->word = (char *)malloc(sizeof(char));
    if (w->word == NULL)
    {
      perror("Error while allocating memory");
      exit(1);
    }
    strcpy(w->word, "");
    w->frequency = 0;
    w->next = NULL;
  }
  else if (w == NULL)
  {
    perror("Error while allocating memory");
  }
  return w;
}

//function searches the Linkedlist for the word string passed in as an argument.
//returns pointer to the found node always
Word *search(Word *wl, char *wordStr)
{

  while (wl->next != NULL) //iterate until you find the target node or reach the last node
  {
    if (strcmp(wl->word, wordStr) == 0)
    {
      return wl;
    }
    wl = wl->next;
  }
  if (strcmp(wl->word, wordStr) == 0) //case when word is not in linked list
  {
    return wl;
  }
  return wl; //return the word anyways
}

//function to create a new node of the word string passed in as an argument. Returns the pointer to the created word node
Word *makeNode(char *word)
{
  Word *node = initializeWord();
  //update the contents of struct word node
  strcpy(node->word, word);
  node->frequency = 1;
  return node;
}

//function adds a new word node to the linked list. If the word does not exist, create a new word node and add it to the linked list else if the word exists, increment the frequency of the word. Return true if the operation is successful, false otherwise
void addWord(Word *head, char *word)
{

  if (strcmp(head->word, "") == 0) //linked list has no words (no nodes)(empty list)(edge case)
  {

    head->word = (char *)malloc(sizeof(char) * strlen(word));
    if (head->word == NULL)
    {
      perror("Error while allocating memory");
      exit(1);
    }
    strcpy(head->word, word);

    head->frequency = 1;
    head->next = NULL;
  }
  else //if there are nodes in the linked list
  {
    Word *nodeFound = initializeWord();
    nodeFound = search(head, word);         //get the pointer to the found node
    if (strcmp(nodeFound->word, word) != 0) //if node not found (that is nodeFound = pointer to last node of list), then add it to the linked list
    {
      Word *node = makeNode(word);
      nodeFound->next = node;
    }

    else //word already exists in the linked list so we just increment the frequency of that node
    {
      nodeFound->frequency++;
    }
  }
}

//function to free the data inside the word node 'w' and the node itself
void free_node(Word *w)
{
  if (w != NULL)
  {
    free(w->word);
    free(w);
  }
}

//function to free the linkedlist of the the words when the head of the list is passed in as an argument
//I use the helper function (free_node) inside this function to free the data aswell as the current node
void free_list(Word *w)
{
  if (w == NULL)
    return;
  else
  {
    free_list(w->next);
    free_node(w);
  }
}

//function to format the words using sprintf and use write command to output it to the console.
void format_and_print(Word *wl)
{
  char *w = (char *)malloc(sizeof(char) * max_size);
  while (wl != NULL)
  {
    sprintf(w, "%-12s:%3i\n", wl->word, wl->frequency);
    write(1, w, strlen(w));
    wl = wl->next; //go to next word in the linked list
  }
}

//this function is the backbone of our project. It reads the next word in the file and uses a tempBuf variable
//to store the read character into tempBuf and keep concatenating it to a string variable "w" until a space or new line is
//detected. We decided to implement this function to only skip spaces and new lines
void wordFreq(Word *wl, char *filename, int fd)
{
  int fd1;
  if (fd == flag_fd) //that is to read command line argument or env. var.
  {
    //open the file in read only mode
    fd1 = open(filename, O_RDONLY);
    if (fd1 == -1) //error check for fd1
    {
      perror("Something went wrong with open()!\n");
      exit(1);
    }
  }
  else //else use fd1=0 to read from stdin
  { 
    fd1 = fd;
  }

  char tempBuf = ' ';                        //variable to store the read character from the file
  char *w = malloc(sizeof(char) * max_size); //variable 'w' to store the word string (i.e the concatenation of tempBuf characters)
  if (w == NULL)                             //error check for w
  {
    perror("Error while allocating memory");
    exit(1);
  }

  int counter = 0; //counter for number of letters read from file. It helps read a full word (character wise)

  //read the file for the first time to start the loop
  int num_of_bytes = read(fd1, &tempBuf, 1);
  if (num_of_bytes == -1) //error check for read
  {
    perror("Something went wrong with read()!\n");
    exit(1);
  }

  while (num_of_bytes != 0) //keeps reading until end of file
  {
    //this if block keeps concatenating the character in tempBuf to the string 'w'
    //until a space or next line character is not read. if a space or new line char is read,
    //it is skipped and the program goes to the else if block where it adds the null char at the 0th index and prints nothing.
    if (tempBuf != ' ' && tempBuf != '\n')
    {
      //goal is to concatenate the letter in tempBuf to the string in w
      //appending a char to a string
      //source used:
      //https://ubuntuforums.org/showthread.php?t=1016188
      *(w + counter) = tempBuf; //concatenate the letter to the string in tempBuf
      counter++;
    }
    //this else if block does the rest of the job to store the word
    else if (strlen(w) > 0)
    {
      *(w + counter) = '\0'; //mark the end of word
      addWord(wl, w);        // add the word to the list where wl is the head pointer to linkedlist
      // and w is the string that is to be added to the word list
      strcpy(w, "\0"); //mark the end of word by concatenating a null character at the end of string
      counter = 0;     //reset counter to read the next word
    }
    num_of_bytes = read(fd1, &tempBuf, 1); //read again to get the next character
    if (num_of_bytes == -1)                //error check for read
    {
      perror("Something went wrong with read()!\n");
      exit(1);
    }
  }

  int status = close(fd1);
  if (status <= -1) //error check for close
  {
    perror("Something went wrong with close()!\n");
  }
}

int main(int argc, char *argv[])
{
  Word *wl = initializeWord(); //create an empty linked list node
  if (argc >= 2)               //check for command line arguments
  {
    for (int i = 1; i < argc; i++)
    {
      wordFreq(wl, argv[i], flag_fd);
    }
  }
  else
  {
    if (getenv("WORD_FREAK")) //check for environmental variable
    {
      wordFreq(wl, getenv("WORD_FREAK"), flag_fd);
    }
    else //read from stdin (piping)
    {
      wordFreq(wl, "", 0);
    }
  }

  format_and_print(wl);
  free_list(wl);
  return 0;
}
