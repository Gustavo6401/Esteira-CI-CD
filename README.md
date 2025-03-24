# Aprendendo a Linguagem C com uma Esteira de CI/CD

Seja bem-vindo ao meu repositório que é uma esteira de CI/CD. O objetivo é que ele seja portável, eficiente e otimizável para qualquer sistema operacional e que ele faça o deploy de sua aplicação em uma questão de 5 minutos.

Até agora, implementamos as seguintes funcionalidades:

1. Monitor de pastas - Leitor de arquivos .zip, .tar e .7z;
2. Descompactador de Arquivos - Descompacta também arquivos .zip, .tar e .7z;

## E qual o meu Objetivo? 🤔

Meu objetivo é automatizar toda a esteira de CI/CD da Academy SM. Tenho um certo número de APIs rodando em produção numa máquina EC2 e o processo de fazer o deploy por vezes leva horas. O objetivo é que independente da tecnologia, que a minha aplicação leia um arquivo .json contendo as instruções para o deploy da aplicação. Essas informações devem incluir entre outras coisas o comando para se rodar, a tecnologia utilizada, enfim. 

## O que Conseguimos até agora? ✅

1. Instalação do OpenSSH - O OpenSSH recebe uma pasta compactada e o objetivo é que essa pasta seja descompactada diretamente no servidor.
2. Envio dos Arquivos via OpenSSH - Envio os arquivos diretamente pelo OpenSSH afim de manter a qualidade das coisas. 
3. Descompactação de Arquivos - Comecei a descompactar os arquivos afim de automatizar até mesmo essa parte do processo. 

O objetivo é que essa aplicação futuramente rode os comandos necessários para a geração dos arquivos binários que serão servidos por meio do nosso servidor. A aplicação atualmente roda no Windows e desenvolveremos essa versão um pouco mais focada no Windows mesmo.

## Como Posso Rodar Essa Aplicação? 🤔

Bom, rodar essa aplicação exige uma séria de cuidados, especialmente porque vamos precisar mostrar ao Windows Defender que essa aplicação não é potencialmente perigosa. Isso exige uma série de cuidados, tais como:

1. Instalar o OpenSSH;
2. Utilizar o Signtool;
3. Compilar tudo Normalmente.

O foco desse tutorial será para o Windows, pois essa aplicação foi desenvolvida pensando no Windows.

### Utilização do OpenSSH 💻

Você pode Acompanhar esse Tutorial na documentação da Microsoft ou continuar por aqui:

[Tutorial Completo](https://learn.microsoft.com/pt-br/windows-server/administration/openssh/openssh_install_firstuse?tabs=powershell&pivots=windows-server-2022)

#### Para instalar o OpenSSH, é necessário rodar no Windows o seguinte comando:

``` powershell
Get-WindowsCapability -Online | Where-Object Name -like 'OpenSSH*'
```

O comando deve retornar a seguinte informação:

Name  : OpenSSH.Client~~~~0.0.1.0
State : NotPresent

Name  : OpenSSH.Server~~~~0.0.1.0
State : NotPresent

#### Depois, Rode o Comando para Instalar de Vez:

``` powershell
# Install the OpenSSH Client
Add-WindowsCapability -Online -Name OpenSSH.Client~~~~0.0.1.0

# Install the OpenSSH Server
Add-WindowsCapability -Online -Name OpenSSH.Server~~~~0.0.1.0
```

**Importante** - Fique atento se você precisar utilizar regras de Firewall, se você estiver (como eu) utilizando uma instância do EC2, será necessária a configuração de Security Groups. 

### Compilar a Aplicação

Compilar a Aplicação é algo que exige tamanha atenção, pois o objetivo é que geremos os executáveis para que tudo funcione corretamente. Seguiremos o princípio de não instalarmos nada em seu computador (exceto o OpenSSH), esse é necessário. Primeiro de tudo, precisamos compilar o arquivo `uncompact.c` que é responsável por ler o conteúdo da `uncompact.h`

#### Para Criar uma .dll:

Primeiro de tudo, como estamos em um ambiente Windows, é essencial que façamos a compilação de uma .dll. 

``` powershell
gcc -shared -o uncompact.dll uncompact.c -DBBUILD_DLL
```

Se você for parar para analisar em nosso arquivo `uncompact.h`, nós temos um comando muito importante para a Compilação de DLLS, arquivo esse que é importado e visto como uma lib:

``` c
#ifndef UNCOMPACT_H
#define UNCOMPACT_H

#ifdef _WIN32
    #ifdef BUILD_DLL
        #define DLL_EXPORT __declspec(dllexport)
    #else 
        #define DLL_EXPORT __declspec(dllimport)
    #endif
#else 
    #define DLL_EXPORT
#endif

#include <stdio.h>

DLL_EXPORT int uncompact_file(const char *path);

#endif
```

É exatamente isso o que faz o DLLExport. Porém, para usá-los nós precisamos especialmente do `DBBUILD_DLL`.

#### Para Criar o Executável:

A criação do Executável é muito simples, porém, temos que informar que `uncompact.c` contém especiamente uma função que precisamos utilizar a partir de nossa .dll.

A forma de fazer isso é pelo seguinte comando:

``` powershell
gcc -o windows.exe windows.c -L. -luncompact
```

A partir daí, você gerou o seu executável, mas é importante que você não rode a sua aplicação agora, mas que você assine ela por meio do Signtool:

### E Como eu Assino uma Aplicação com o Signtool e para que Ele Serve? 🤔

O Signtool é uma tecnologia muito importante que nos permite mostrar para o Windows, especialmente o Windows Defender que o Aplicativo que desenvolvemos é seguro. Ele fica contido em um diretório e admito que não consegui criar variáveis de Ambiente para Ele. Vale lembrar que o Signtool só serve para arquivos que você gerou e especialmente em sua própria máquina. Esse processo precisa ser feito pois esse arquivo monitora um diretório completo da sua máquina, com tudo o que está envolvido nele. Muitos vírus de Computador fazem isso, mas vale lembrar também, que muitos vírus de computador monitoram diretórios completos no computador das vítmas. 

#### Primeiro: Vamos ao Diretório Dele

O diretório do Signtool não é tão simples de ser encontrado e admito não ter conseguido criar variáveis de ambiente para ele, nesse caso, vamos manualmente até o diretório, o caminho completo (ao menos em meu PC) é:

``` powershell
"C:\\Program Files\\Windows Kits\\10\\bin\\10.0.22621.0\\x64\\signtool.exe"
```

Longo né? 😮‍💨

Bom, agora que chegamos até aqui, você precisa rodar o seguinte comando: 

``` powershell
.\signtool sign /a /fd sha256 "C:\<CAMINHO COMPLETO>\HelloWorld\windows.exe"
```

Dentro desse comando, são necessárias informações como escolher o melhor certificado instalado no Computador e até mesmo a flag `/fd` é responsável por informar o algoritmo de incriptação, eu sempre utilizo SHA256. Para mais informações, consulte a documentação da Microsoft no Link:

[Documentação](https://learn.microsoft.com/en-us/dotnet/framework/tools/signtool-exe)

### Finalmente, vamos rodar a aplicação

Volte à pasta de sua aplicação.

Por fim, rode:

``` powershell
.\windows.exe
```

Agora, todas as pastas compactadas com .zip e .tar que forem enviadas para aquela pasta serão automaticamente descompactadas. Isso iria facilitar muito o meu trabalho. Especialmente na pasta da esteira de CI/CD.

Obrigado pela atenção! 