#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node Node;
// Gelecek txt dosyasındaki görev parçacıkları
struct Node {
  int id;
  int gelisZamani;
  int sure;
  int oncelik;
  char gorevTuru[39];
  char konum[39];
  Node *prev;
  Node *next;
};

Node *nodeEkle(Node *root, int id, int gelisZamani, int sure, int oncelik,
               char *gorevTuru, char *konum);
Node *nodeSil(Node *root, int id);

void listeyiYazdir(Node *root);
Node *listeSonunaGel(Node *root);

Node *dosyadanVeriCekme(Node *root, FILE *dosya);

int main() {
  // Listenin ilk elemanı
  Node *root = NULL;
  FILE *dosya = fopen("gorevler.txt", "r");
  root = dosyadanVeriCekme(root, dosya);
  listeyiYazdir(root);
  return 0;
}
void listeyiYazdir(Node *root) {
  Node *imlecNodesi = root;
  while (imlecNodesi != NULL) {
    printf(
        "ID: %d, Geliş: %d, Süre: %d, Öncelik: %d, Görev Türü: %s, Konum: %s\n",
        imlecNodesi->id, imlecNodesi->gelisZamani, imlecNodesi->sure,
        imlecNodesi->oncelik, imlecNodesi->gorevTuru, imlecNodesi->konum);
    imlecNodesi = imlecNodesi->next;
  }
}

Node *nodeEkle(Node *root, int id, int gelisZamani, int sure, int oncelik,
               char *gorevTuru, char *konum) {
  Node *eklenecekNode = (Node *)malloc(sizeof(Node));
  eklenecekNode->id = id;
  eklenecekNode->gelisZamani = gelisZamani;
  eklenecekNode->sure = sure;
  eklenecekNode->oncelik = oncelik;
  strcpy(eklenecekNode->gorevTuru, gorevTuru);
  strcpy(eklenecekNode->konum, konum);
  eklenecekNode->next = NULL;

  if (root == NULL) {
    eklenecekNode->prev = NULL;
    return eklenecekNode;
  }

  Node *imlecNodesi = listeSonunaGel(root);
  eklenecekNode->prev = imlecNodesi;
  imlecNodesi->next = eklenecekNode;
  return root;
}

Node *listeSonunaGel(Node *root) {
  if (root == NULL) {
    printf("Listenin sonuna gelinemedi çünkü liste boş!\n");
    return NULL;
  }
  Node *imlecNodesi = root;
  while (imlecNodesi->next != NULL) {
    imlecNodesi = imlecNodesi->next;
  }
  return imlecNodesi;
}
Node *nodeSil(Node *root, int id) {
  if (root == NULL) {
    printf("Liste boş!\n");
    return NULL;
  }

  Node *imlec = root;

  while (imlec != NULL) {
    if (imlec->id == id) {
      if (imlec->prev == NULL) {
        root = imlec->next;
        if (root != NULL) {
          root->prev = NULL;
        }
      } else {
        imlec->prev->next = imlec->next;
        if (imlec->next != NULL) {
          imlec->next->prev = imlec->prev;
        }
      }

      free(imlec);
      return root;
    }
    imlec = imlec->next;
  }

  printf("ID: %d bulunamadi!\n", id);
  return root;
}

Node *dosyadanVeriCekme(Node *root, FILE *dosya) {
  if (dosya == NULL) {
    printf("Dosya açılamadı!\n");
    return root;
  }
  int id, gelisZamani, sure, oncelik;
  char gorevTuru[39], konum[39];
  while (fscanf(dosya, "%d %d %d %d %38s %38s", &id, &gelisZamani, &sure,
                &oncelik, gorevTuru, konum) == 6) {
    root = nodeEkle(root, id, gelisZamani, sure, oncelik, gorevTuru, konum);
  }
  fclose(dosya);
  return root;
}
