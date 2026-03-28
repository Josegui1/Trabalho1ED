# Trabalho1ED

## Descrição do Projeto
Neste Projeto implementamos um sistema de gerenciamento de reservar de salas de aulas ultilizando a linguagem C++. O sistema permite cadastrar salas, reservar horários, cancelar reservas e consultar os horários ocupados das salas.

## Instruções de Compilação e Uso
Para compilar e executar o projeto, siga as instruções abaixo:
1. Tenha o compilador C++ no seu ambiente de desenvolvimento. (como o g++)
2. Acesse o diretório do projeto pelo terminal e execute o seguinte comando:
```bash
 g++ .\main.cpp .\ReservationSystem.cpp .\ReservationRequest.cpp -o reservation_system.exe
```
3. Após a compilação, execute o programa com o comando:
```bash
 .\reservation_system.exe
```
## Organização Interna dos Dados

O sistema utiliza duas estruturas de dados principais:

**Array de capacidades (`room_capacities`):** um array de inteiros de tamanho `room_count` que armazena a capacidade máxima de cada sala. O acesso é direto pelo índice da sala, com custo O(1).

**Array de listas encadeadas (`reservations`):** cada posição do array corresponde a uma sala e aponta para o início de uma lista encadeada de nós (`ReservationNode`). Cada nó armazena os dados de uma reserva (disciplina, dia, horário de início e término). As reservas são inseridas já ordenadas por dia da semana e horário de início, o que facilita a exibição da grade sem necessidade de ordenação posterior.

Essa combinação foi escolhida por ser simples, eficiente em memória e adequada ao volume de dados esperado. As principais operações (`reserve`, `cancel`, `printSchedule`) têm custo O(n·k), onde n é o número de salas e k é a quantidade média de reservas por sala.
