# 📘 Projeto Passa a Bola


## 📝 Descrição do Projeto
O projeto **Passa a Bola** tem como objetivo monitorar se a bola sai ou não de uma quadra esportiva, utilizando sensores ultrassônicos para detectar a passagem da bola em pontos estratégicos da linha.  

A lógica é simples:  
- Se a bola passar pelo **sensor da esquerda (Sensor 2)** e não retornar para o **sensor da direita (Sensor 1)**, significa que a bola saiu da quadra. Nesse caso, **LED e buzzer são ativados** para indicar a saída.  
- Caso a bola volte e passe novamente pelo **sensor da direita (Sensor 1)**, o alerta é desativado.  

Além disso, os dados de cada sensor são enviados em tempo real para o **ThingSpeak**, permitindo acompanhamento remoto.  

---

## 🏗️ Arquitetura Proposta

### Diagrama (simplificado em texto)
```
                ┌────────────┐
                │   Sensor 1 │  (Direita)
                └──────┬─────┘
                       │
                       │
                ┌──────┴─────┐
                │   ESP32    │─── Wi-Fi ───> ThingSpeak
                └──────┬─────┘
                       │
          ┌────────────┴────────────┐
          │                         │
     ┌────┴─────┐              ┌────┴─────┐
     │   LED    │              │  Buzzer  │
     └──────────┘              └──────────┘
                       │
                ┌──────┴─────┐
                │   Sensor 2 │  (Esquerda)
                └────────────┘
```

### Explicação
- O **ESP32** é o núcleo do sistema, recebendo leituras dos dois sensores ultrassônicos.  
- Quando identificado que a bola saiu, ele **aciona LED e buzzer** como alerta local.  
- Simultaneamente, envia os dados para a nuvem via **ThingSpeak**, permitindo análise remota.  

---

## 📦 Recursos Necessários
- 1x **ESP32**  
- 2x **Sensores ultrassônicos HC-SR04**  
- 1x **LED**  
- 1x **Buzzer**  
- Protoboard + jumpers  
- Conexão Wi-Fi  

---

## 🚀 Instruções de Uso
1. Monte o circuito conforme o diagrama de arquitetura.  
2. Carregue o código no ESP32 utilizando a **Arduino IDE**.  
3. Configure a conexão Wi-Fi e a chave da API do **ThingSpeak** no código:  
   ```cpp
   const char* ssid = "SEU_WIFI";
   const char* password = "SUA_SENHA";
   const char* apiKey = "SUA_API_KEY";
   ```
4. Abra o **Serial Monitor** para visualizar as leituras em tempo real.  
5. Acompanhe os dados também pelo painel do **ThingSpeak**.  
6. Quando a bola sair da quadra:  
   - **LED acende**  
   - **Buzzer toca**  
7. Quando a bola voltar:  
   - **LED apaga**  
   - **Buzzer desliga**  

---

## 👥 Integrantes
- Vítor Silva Borsato RM:561805   
- João Pedro Godinho Passiani RM:561602​
- Gabriel Molinari Droppa RM:562082
- Isabela de Deus RM: 565988

---

## 🎥 Vídeo de Demonstração
👉 [Assista ao vídeo aqui](COLOQUE_O_LINK_DO_VIDEO_AQUI)

---

## 🎮 Simulador do Wokwi
👉 [Clique aqui para testar](https://wokwi.com/projects/441173414311135233)