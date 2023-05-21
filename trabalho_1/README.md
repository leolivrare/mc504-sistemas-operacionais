# MC504 - Sistemas Operacionais - Projeto Multithread

## Introdução

Este projeto tem como objetivo a implementação e observação de um problema clássico de sincronização em um ambiente de processos multithread. O foco principal é explorar os conceitos de sincronização utilizando semáforos e criar uma animação que facilite a visualização do processo.

### Problema Escolhido: Construindo H2O
O problema escolhido para este projeto é conhecido como *"Construindo H2O"* e é descrito na página 143 do livro "The Little Book of Semaphores", escrito por Allen B. Downey. Neste problema, duas threads são utilizadas, uma responsável por produzir moléculas de oxigênio e outra por produzir moléculas de hidrogênio. O objetivo é criar uma molécula de água, composta por dois átomos de hidrogênio e um átomo de oxigênio.

Para garantir a correta formação das moléculas de água, é necessário criar uma barreira que impeça as threads de avançarem até que uma molécula esteja pronta. Além disso, é importante garantir que todas as threads da molécula chamem a função "generate_h2o()" antes das threads da próxima molécula iniciarem o processo.

A escolha desse problema se deve à sua complexidade e à necessidade de sincronização entre as threads para garantir a formação correta das moléculas. Ele proporciona um cenário ideal para explorar os conceitos de sincronização e demonstrar a importância do uso de semáforos nesse contexto.

## Como executar o programa (linux)

### Requisitos

- GCC (GNU Compiler Collection)
- Make

### Como executar

1. **Clone o repositório para o seu computador**: ```git clone https://github.com/leolivrare/mc504-sistemas-operacionais```
2. **Acesse o diretório do projeto**: ```cd mc504-sistemas-operacionais/trabalho_1```
3. **Compile o programa usando o Makefile**: ```make compile```
    
    *Isso irá compilar o programa e gerar o executável.*
4. **Execute o programa**: ```make run```
    
    *Isso irá executar o programa compilado e mostrará a saída no terminal.*

#### Comandos adicionais

- **Se você quiser realizar a compilação e execução em um único comando, você pode usar o seguinte comando:** ```make compile-and-run```
   
   *Isso irá compilar o programa e, em seguida, executá-lo em um único passo.*

- **Para limpar os arquivos gerados durante a compilação, você pode executar o seguinte comando:** ```make clean```
   
   *Isso irá remover os arquivos temporários e o executável gerado.*


**Importante:** Certifique-se de adaptar as instruções de acordo com o nome do seu projeto e o local onde você clonou o repositório.

## Sobre a implementação
A implementação do problema "Construindo H2O" foi baseada no pseudocódigo fornecido no livro "The Little Book of Semaphores". Utilizamos dois semáforos (um para hidrogênio e outro para oxigênio), um mutex e uma barreira para garantir a sincronização correta entre as threads.

Na thread do oxigênio, é adquirido o mutex, um oxigênio é gerado e é verificado se existem hidrogênios suficientes para formar uma molécula de água. Caso haja hidrogênios suficientes, são sinalizados os semáforos de oxigênio e hidrogênio. Em seguida, a thread aguarda o sinal do semáforo de oxigênio, invoca a função "generate_h2o()" para representar a criação de uma molécula de água, espera pela barreira e libera o mutex. A mesma lógica é aplicada à thread do hidrogênio.

Durante a implementação, surgiram dois problemas a serem solucionados. O primeiro estava relacionado à animação, pois as threads eram criadas muito rapidamente. Para solucionar esse problema, foi introduzido um sleep() para tornar a animação mais lenta. Além disso, foi utilizado outro mutex para garantir que apenas a função "animation()" tivesse acesso à região crítica para impressão.

O segundo problema ocorreu devido à presença da função "generate_h2o()" tanto na thread do hidrogênio quanto na do oxigênio, resultando na impressão duplicada da quantidade de água gerada. Essa duplicação foi corrigida na implementação.

Por fim, durante a implementação do problema "Construindo H2O", também foi explorado o conceito de barreira. A barreira foi preconfigurada para aceitar um número N de threads antes de sinalizar a continuação. Isso permitiu coordenar a montagem das moléculas de água, garantindo que não ocorresse a montagem simultânea de duas moléculas.

Espera-se que esta implementação e observação do problema "Construindo H2O" contribuam para uma compreensão aprofundada dos conceitos de sincronização em processos multithread e demonstrem a importância dos semáforos como ferramentas de controle de concorrência.
