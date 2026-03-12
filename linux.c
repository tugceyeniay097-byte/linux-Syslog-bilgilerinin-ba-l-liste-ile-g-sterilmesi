#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct SyslogNode {
    int logID;
    char timestamp[25];
    char level[15];
    char message[256];
    struct SyslogNode* next; // Sonraki logu gösterir
    struct SyslogNode* prev; // Önceki logu gösterir (Geriye dönük arama için)
} SyslogNode;

// Listenin baþý ve sonu için pointer yönetimi
SyslogNode* head = NULL;
SyslogNode* tail = NULL;
int logCounter = 1;

void getCurrentTime(char* buffer) {
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 25, "%Y-%m-%d %H:%M:%S", timeinfo);
}

void addSyslog(const char* level, const char* msg) {
    SyslogNode* newNode = (SyslogNode*)malloc(sizeof(SyslogNode));
    if (newNode == NULL) {
        printf("Kritik Hata: Bellek tahsis edilemedi!\n");
        return;
    }

    newNode->logID = logCounter++;
    strcpy(newNode->level, level);
    strcpy(newNode->message, msg);
    getCurrentTime(newNode->timestamp); // Zamaný otomatik ata
    
    newNode->next = NULL;

    // Eðer liste tamamen boþsa
    if (head == NULL) {
        newNode->prev = NULL;
        head = tail = newNode;
    } else {
        // Liste boþ deðilse, yeni logu en sona (tail) ekle ve çift yönlü baðla
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode; // Yeni kuyruk (en güncel log) artýk bu düðüm
    }
}

void displayLogsNormal() {
    SyslogNode* current = head;
    printf("\n>>> LINUX SYSLOG KAYITLARI (ESKIDEN YENIYE - KRONOLOJIK) <<<\n");
    printf("%-5s | %-20s | %-10s | %-s\n", "ID", "ZAMAN", "SEVIYE", "MESAJ");
    printf("----------------------------------------------------------------------\n");
    
    while (current != NULL) {
        printf("%-5d | %-20s | %-10s | %-s\n", 
               current->logID, current->timestamp, current->level, current->message);
        current = current->next;
    }
    printf("----------------------------------------------------------------------\n");
}

void displayLogsReverse() {
    SyslogNode* current = tail; // Taramaya kuyruktan (en yeni logdan) baþla
    printf("\n>>> LINUX SYSLOG KAYITLARI (YENIDEN ESKIYE - TERS OKUMA) <<<\n");
    printf("%-5s | %-20s | %-10s | %-s\n", "ID", "ZAMAN", "SEVIYE", "MESAJ");
    printf("----------------------------------------------------------------------\n");
    
    while (current != NULL) {
        printf("%-5d | %-20s | %-10s | %-s\n", 
               current->logID, current->timestamp, current->level, current->message);
        current = current->prev; // 'prev' pointerý sayesinde geriye doðru git
    }
    printf("----------------------------------------------------------------------\n");
}

void freeMemory() {
    SyslogNode* current = head;
    while (current != NULL) {
        SyslogNode* temp = current;
        current = current->next;
        free(temp); // Düðümü bellekten sil
    }
}

int main() {
   
    addSyslog("INFO", "Sistem baslatildi, çekirdek modulleri yukleniyor.");
    addSyslog("INFO", "Network servisi (eth0) aktif edildi.");
    addSyslog("WARNING", "Bellek kullanimi %85 seviyesine ulasti, swap alani hazirlaniyor.");
    addSyslog("ERROR", "Disk okuma hatasi: /dev/sda1 sektor arizasi.");
    addSyslog("CRITICAL", "Sistem kernel panic verdi! Kapatiliyor...");

    displayLogsNormal();

    displayLogsReverse();

    freeMemory();

    return 0;
}
