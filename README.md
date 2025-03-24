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

Obrigado pela atenção! 