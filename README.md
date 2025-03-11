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

Obrigado pela atenção! 