#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <windows.h>
#include <string.h>

typedef char string[100];
typedef struct tChild *adrChild;
typedef struct tParent *adrParent;

typedef struct
{
	string namaServer;
	string lokasiServer;
} Server;

typedef struct
{
	string username;
	string password;
} User;

typedef struct tParent
{
	Server server;
	adrParent nextParent;
	adrChild firstChild;
} Parent;

typedef struct tChild
{
	User anggota;
	adrChild nextChild;
} Child;

typedef struct
{
	adrParent first;
} ListParent;

void showMenu();
int isEmpty(ListParent L);
void createEmpty(ListParent *L);

Server makeServer(string namaServer, string namaNegara);
adrParent alokasiServer(Server serverBaru);
int haveChild(adrParent P);
void insertFirstParent(ListParent *L, Server databaru);
void insertLastParent(ListParent *L, Server databaru);
void deleteFirstParent(ListParent *L);
adrParent findParentByNamaServer(ListParent L, string namaServer);
void printServerByNegara(ListParent L, string namaNegara);

User makeUser(string username, string password);
adrChild AlokasiC(User userBaru);
void insertFirstChildToParentServer(ListParent *L, string namaServer, User userBaru);
void deleteFirstChild(ListParent *L, string namaServer);
void deleteLastChild(ListParent *L, string namaServer);
void printChild(adrChild C);
void printAll(ListParent L);
void cariUser(ListParent L, string username);
void hapusUser(ListParent *L, string username);