[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MS5837

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ms5837/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der MS5837 besteht aus einem piezoresistiven Sensor und einer integrierten Schaltung für die Sensorschnittstelle. Die Hauptfunktion des MS5837 besteht darin, die unkompensierte analoge Ausgangsspannung des piezoresistiven Drucksensors in einen 24-Bit-Digitalwert umzuwandeln und einen 24-Bit-Digitalwert für die Temperatur des Sensors bereitzustellen. Er kann verwendet werden in Fitnesstrackern, Drohnen, Fahrradcomputern und Co.

LibDriver MS5837 ist der MS5837-Vollfunktionstreiber, der von LibDriver gestartet wurde. Er bietet Temperaturmessung, Druckmessung und andere Funktionen. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver MS5837-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver MS5837 IIC.

/test enthält den Testcode des LibDriver MS5837-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver MS5837-Beispielcode.

/doc enthält das LibDriver MS5837-Offlinedokument.

/Datenblatt enthält MS5837-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

#### example basic

```C
#include "driver_ms5837_basic.h"

uint8_t res;
uint32_t i;
uint32_t times;

/* basic init */
res = ms5837_basic_init(MS5837_TYPE_02BA01);
if (res != 0)
{
    return 1;
}

...
    
times = 3;

...
    
for (i = 0; i < times; i++)
{
    float temperature_c;
    float pressure_mbar;

    /* read data */
    res = ms5837_basic_read(&temperature_c, &pressure_mbar);
    if (res != 0)
    {
        (void)ms5837_basic_deinit();

        return 1;
    }

    /* output */
    ms5837_interface_debug_print("ms5837: %d/%d.\n", i + 1, times);
    ms5837_interface_debug_print("ms5837: temperature is %0.2fC.\n", temperature_c);
    ms5837_interface_debug_print("ms5837: pressure is %0.2fmbar.\n", pressure_mbar);

    /* delay 1000ms */
    ms5837_interface_delay_ms(1000);
    
    ...
}

...
    
/* deinit */
(void)ms5837_basic_deinit();

return 0;
```

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/ms5837/index.html](https://www.libdriver.com/docs/ms5837/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.