# Projeto ED

Projeto em C para a disciplina de Estruturas de Dados, organizado por módulos dentro de `src` com os cabeçalhos ao lado do respetivo código e os dados de execução separados.

## Estrutura

| Pasta/Ficheiro | Função |
| --- | --- |
| `src/supermercado` | Lógica principal da aplicação e interface da simulação. |
| `src/uteis` | Utilitários e código de suporte transversal. |
| `src/pessoas` | Código da entidade pessoa e listas de pessoas. |
| `src/clientes` | Código da entidade cliente e listas de clientes. |
| `src/produtos` | Código da entidade produto e listas de produtos. |
| `src/caixas` | Código da caixa. |
| `src/relogio` | Código do relógio da simulação. |
| `dados/clientes.txt` | Clientes de teste para carregar no arranque. |
| `dados/Configuracao.txt` | Parâmetros da simulação. |
| `dados/Dados.txt` | Dados da simulação ainda por implementar no carregamento. |
| `dados/DadosFormatoExemplo.txt` | Exemplo de formato esperado. |
| `dados/funcionarios.txt` | Funcionários do supermercado. |
| `dados/produtos.txt` | Catálogo de produtos. |
| `dados/logs.txt` | Ficheiro de registo de avisos e erros. |
| `.vscode` | Tasks de build e execução no VS Code. |

## Build

O projeto é compilado pelas tasks do VS Code:

- `Build C Project (Windows/Linux)`
- `Run Program`

O ficheiro `compile.sh` foi removido porque duplicava essa responsabilidade.

## O que ainda falta fazer

- Implementar a leitura real de `Dados.txt` em `CarregarDadosSimulacao`.
- Inicializar e gerir corretamente as caixas de pagamento.
- Implementar a entrada, movimentação e saída de clientes na simulação.
- Ligar clientes, filas e produtos ao fluxo real de atendimento.
- Destruir corretamente toda a memória alocada no fim do programa.
- Revisar mensagens de debug e substituir o que for preciso por logging consistente.
- Validar os ficheiros de configuração e de dados com erros de formato.
- Criar testes mínimos de compilação e de funcionamento da simulação.

## Estado atual

O projeto já está melhor separado por responsabilidade, mas a simulação ainda está incompleta e há várias partes marcadas como `TODO`.