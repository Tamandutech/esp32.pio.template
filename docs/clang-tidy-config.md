# Configuração do Clang-Tidy para Projetos ESP-IDF

Este projeto está configurado com uma configuração unificada do clang-tidy otimizada para projetos ESP-IDF, com exceções específicas para padrões comuns do framework.

## Arquivo de Configuração Principal

### `.clang-tidy` (Configuração Unificada)
Configuração única que funciona tanto para desenvolvimento local quanto para Pull Requests, com exceções específicas para ESP-IDF:

## Checks Habilitados

### **Erros Críticos (Sempre Ativos)**
- **cppcoreguidelines-pro-bounds-***: Verificações de bounds checking
- **cppcoreguidelines-pro-type-***: Verificações de tipo
- **cert-***: Verificações de segurança CERT
- **clang-analyzer-core-***: Análise estática core
- **clang-analyzer-cplusplus-***: Análise específica C++
- **clang-analyzer-deadcode-***: Detecção de código morto
- **clang-analyzer-security-***: Análise de segurança
- **performance-***: Verificações de performance
- **readability-misleading-indentation**: Indentação confusa
- **readability-simplify-boolean-expr**: Expressões booleanas simplificáveis

### **Warnings de Estilo (Ativos com Exceções)**
- **readability-identifier-naming**: Nomenclatura de identificadores
- **readability-uppercase-literal-suffix**: Sufixos maiúsculos em literais

## Exceções Específicas para ESP-IDF

### **1. Função `app_main()`**
```yaml
- key: readability-identifier-naming.FunctionIgnoredRegexp
  value: '^app_main$'
```
**Motivo**: `app_main()` é o ponto de entrada padrão do ESP-IDF e não segue convenções de nomenclatura camelCase.

### **2. Constantes em SCREAMING_SNAKE_CASE**
```yaml
- key: readability-identifier-naming.VariableIgnoredRegexp
  value: '^[A-Z_]+$'
```
**Motivo**: Constantes como `ROBOT_WIDTH`, `MAX_SPEED`, `WHEEL_CIRCUMFERENCE` são padrão em projetos ESP-IDF.

### **3. Magic Numbers**
- **Completamente ignorado**: `readability-magic-numbers` não está na lista de checks
- **Motivo**: Números mágicos são comuns em projetos embarcados e podem ser apropriados

## Configuração de Nomenclatura

### **Padrões Enforçados**
- **Namespaces**: `CamelCase` (ex: `RobotEnv`)
- **Classes**: `CamelCase` (ex: `PathController`)
- **Structs**: `CamelCase` (ex: `PathControllerParamSchema`)
- **Funções**: `camelBack` (ex: `getLinePosition`)
- **Variáveis**: `camelBack` (ex: `sensorValues`)
- **Parâmetros**: `camelBack` (ex: `sensorQuantity`)
- **Membros**: `camelBack` (ex: `lastPosition`)
- **Membros Privados**: Sufixo `_` (ex: `lastPosition_`)
- **Membros Protegidos**: Sufixo `_` (ex: `onLine_`)

### **Exceções**
- **`app_main()`**: Ignorado (padrão ESP-IDF)
- **Constantes**: `SCREAMING_SNAKE_CASE` ignorado (ex: `ROBOT_WIDTH`)

## Configuração do PlatformIO

### `platformio.ini`
```ini
check_tool = clangtidy
check_flags =
  clangtidy: --config-file=.clang-tidy
```

**Nota**: Removemos `--fix` para evitar modificações automáticas do código.

## Configuração do GitHub Actions

### `.github/workflows/lint.yml`
```yaml
- name: Copy PR-specific config
  run: cp .clang-tidy-pr .clang-tidy
- name: Run cpp-linter
  uses: cpp-linter/cpp-linter-action@v2
```

**Nota**: Atualmente usando configuração unificada, mas mantemos a estrutura para futuras customizações.

## Exemplos de Warnings Detectados

### **✅ Warnings que Aparecem**
```cpp
float value = 3.14f;  // Warning: sufixo minúsculo 'f'
int sensor_values[12]; // Warning: nomenclatura não segue camelBack
```

### **✅ Warnings Suprimidos**
```cpp
void app_main() { }           // OK: função ESP-IDF padrão
const float ROBOT_WIDTH = 4;  // OK: constante em SCREAMING_SNAKE_CASE
const int MAX_SPEED = 100;    // OK: constante em SCREAMING_SNAKE_CASE
float value = 3.14F;          // OK: sufixo maiúsculo 'F'
int sensorValues[12];         // OK: nomenclatura camelBack
```

## Benefícios da Configuração

### **Para Projetos ESP-IDF**
- **Compatibilidade**: Funciona com padrões ESP-IDF (`app_main`, constantes)
- **Flexibilidade**: Permite constantes em `SCREAMING_SNAKE_CASE`
- **Consistência**: Enforça nomenclatura para código regular

### **Para Desenvolvimento**
- **Menos Ruído**: Ignora warnings apropriados para embarcados
- **Foco em Problemas**: Detecta erros críticos e problemas reais
- **Padrões Claros**: Nomenclatura consistente para código novo

### **Para Pull Requests**
- **Configuração Unificada**: Mesma configuração local e PR
- **Menos Poluição**: Apenas problemas importantes são comentados
- **Melhor Experiência**: Desenvolvedores focam no que importa

## Comandos Úteis

### **Verificar Arquivo Específico**
```bash
pio check --src-filters="+<src/path/to/file.hpp>" --verbose
```

### **Verificar Todo o Projeto**
```bash
pio check -e esp32
```

### **Executar Clang-Tidy Diretamente**
```bash
clang-tidy src/path/to/file.cpp --config-file=.clang-tidy
```

## Manutenção

### **Adicionar Nova Exceção**
1. Edite `.clang-tidy`
2. Adicione nova entrada em `CheckOptions`
3. Teste com `pio check`
4. Documente a exceção neste arquivo

### **Modificar Padrões de Nomenclatura**
1. Edite as configurações `readability-identifier-naming.*`
2. Ajuste regex de exceções se necessário
3. Teste com arquivos existentes
4. Atualize documentação