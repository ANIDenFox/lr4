#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LogEntry {
    int id;
    char *message;
    char *timestamp;
} LogEntry;

LogEntry* create_entry(int id, const char *msg, const char *time) {
    LogEntry *entry = (LogEntry*)malloc(sizeof(LogEntry));
    if (!entry) return NULL;
    
    entry->id = id;
    entry->message = strdup(msg);
    // ВИПРАВЛЕНО: Прибрано друге перезаписування strdup, що викликало Memory Leak
    entry->timestamp = strdup(time);
    
    return entry;
}

void free_entry(LogEntry *entry) {
    if (!entry) return;
    // ВИПРАВЛЕНО: Видалено дублюючий виклик free(entry->message); (усунення Double Free)
    free(entry->message);
    free(entry->timestamp);
    free(entry);
}

void format_log_header(const char *title) {
    // ВИПРАВЛЕНО: Збільшено розмір буфера (або можна використати strncpy) для уникнення Stack Buffer Overflow
    char header_buffer[128]; 
    strncpy(header_buffer, title, sizeof(header_buffer) - 1);
    header_buffer[sizeof(header_buffer) - 1] = '\0'; // Гарантія нуль-термінації
    printf("Header: %s\n", header_buffer);
}

int main() {
    printf("--- Запуск програми журналу подій ---\n");
    
    // 1. Тест заголовочного буфера
    format_log_header("Цей заголовок є занадто довгим для 16 байт");
    
    // 2. Тест створення запису
    LogEntry *entry = create_entry(101, "Системна помилка підключення", "12:45:30");
    if (entry) {
        printf("Запис [%d] [%s]: %s\n", entry->id, entry->timestamp, entry->message);
        free_entry(entry);
    }
    
    return 0;
}