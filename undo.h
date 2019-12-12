typedef struct{}Player;
void fillWith0s(int*, int*, int);
void addUndo(int*,int, int, int);
void addRedo(int*, int, int, int);
void deleteLine(char*, int, int, int);
void undoPlay(char*, int, int*, int, int*, int*, Player*, Player*, int*);
int checkBoxAgain(char*, int, int, int, char*);
void assignBoxAgain(char*, int, int, int);
void redoPlay(int*, int*, int*, int, int*)
