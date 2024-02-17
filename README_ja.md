[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MS5837

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ms5837/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MS5837 は、ピエゾ抵抗センサーとセンサー インターフェイス集積回路で構成されています。 MS5837 の主な機能は、ピエゾ抵抗圧力センサーからの補償されていないアナログ出力電圧を 24 ビットのデジタル値に変換することと、センサーの温度に 24 ビットのデジタル値を提供することです。 フィットネス トラッカー、ドローン、サイクル コンピューターなど。

LibDriver MS5837 は、LibDriver によって起動される MS5837 フル機能ドライバーです。温度読み取り、圧力読み取り、およびその他の機能を提供します。 LibDriver は MISRA 準拠です。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver MS5837のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver MS5837用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver MS5837ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver MS5837プログラミング例が含まれています。

/ docディレクトリには、LibDriver MS5837オフラインドキュメントが含まれています。

/ datasheetディレクトリには、MS5837データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/ms5837/index.html](https://www.libdriver.com/docs/ms5837/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。