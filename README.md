Linux Syslog Simülasyonu – Çift Yönlü Bağlı Liste
Proje Hakkında

Bu program, Linux sistem günlüklerini (syslog) simüle eden bir C uygulamasıdır. Gerçek bir syslog dosyasını okumak yerine, loglar RAM üzerinde oluşturulmakta ve bir çift yönlü bağlı liste (doubly linked list) yapısında tutulmaktadır. Böylece log kayıtları hem kronolojik (eski → yeni) hem de ters kronolojik (yeni → eski) sırayla okunabilir.

Özellikler

Her log kaydı bir düğüm (node) olarak temsil edilir.

Node içerisinde:

Log ID (logID)

Zaman damgası (timestamp)

Log seviyesi (level) – INFO, WARNING, ERROR, CRITICAL

Log mesajı (message)

İleri ve geri pointerlar (next, prev) bulunur.

Liste başı (head) ve kuyruk (tail) pointerları ile listenin hem başından hem de sonundan erişim mümkündür.

Log ID’leri otomatik olarak artan bir sayaç (logCounter) ile atanır.

Loglar eklenirken sistemin güncel zamanı getCurrentTime() fonksiyonu ile otomatik olarak eklenir.

Program logları hem normal sıralama (eskiden yeniye) hem de ters sıralama (yeniden eskiye) ile ekrana yazdırabilir.

Dinamik olarak ayrılan bellek, freeMemory() fonksiyonu ile serbest bırakılır ve hafıza sızıntısı önlenir.

Kurulum ve Çalıştırma

C derleyicisine sahip olun (örn. GCC).

Kod dosyasını (syslog_simulation.c) bir dizine kaydedin.

Terminal veya komut satırından derleyin:

gcc syslog_simulation.c -o syslog_sim

Programı çalıştırın:

./syslog_sim

Çıktıda loglar hem kronolojik hem de ters kronolojik olarak görüntülenecektir.

Fonksiyonlar

getCurrentTime(char* buffer) – Sistem zamanını alır ve okunabilir formata çevirir.

addSyslog(const char* level, const char* msg) – Yeni log ekler ve düğümleri bağlar.

displayLogsNormal() – Logları eski → yeni sıralamayla ekrana yazdırır.

displayLogsReverse() – Logları yeni → eski sıralamayla ekrana yazdırır.

freeMemory() – Dinamik bellekten tüm düğümleri temizler.

Avantajlar

Çift yönlü bağlı liste sayesinde loglar üzerinde ileri ve geri tarama yapılabilir.

Kronolojik sırayla ekleme ve görüntüleme sayesinde sistem olaylarını hızlı incelemek mümkündür.

Dinamik bellek kullanımı, gereksiz hafıza tüketimini önler.
