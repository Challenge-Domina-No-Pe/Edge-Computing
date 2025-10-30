# ⚽ Projeto Passa a Bola - Versão Servidor Web

## 📝 Descrição do Projeto

O projeto **Passa a Bola** tem como objetivo detectar se uma bola está **dentro**, **na linha**, ou **fora de uma quadra**, utilizando **dois sensores ultrassônicos HC-SR04** conectados a um **ESP32**.

Diferente da versão anterior (com LED e buzzer), esta versão envia os dados dos sensores diretamente para um **servidor web local**, que exibe as informações em tempo real em uma página HTML estilizada.

A lógica de detecção é:

* ✅ **Bola em campo:** quando nenhum sensor detecta a bola.
* ⚪ **Na linha:** quando os dois sensores detectam a bola simultaneamente.
* ❌ **Fora do campo:** quando apenas o sensor 2 detecta a bola e o sensor 1 não.

---

## 🏗️ Arquitetura Proposta

### Diagrama Simplificado

```
                ┌────────────┐
                │  Sensor 1  │  (Direita)
                └──────┬─────┘
                       │
                ┌──────┴─────┐
                │   ESP32    │─── Wi-Fi ───> Servidor Web Local
                └──────┬─────┘
                       │
                ┌──────┴─────┐
                │  Sensor 2  │  (Esquerda)
                └────────────┘
```

### Explicação

* O **ESP32** lê continuamente os valores dos sensores ultrassônicos.
* Ele envia as informações para o **servidor web**, que as exibe de forma clara e dinâmica em uma interface HTML.
* Assim, é possível visualizar o estado da bola **em tempo real** pelo navegador.

---

## 📦 Recursos Necessários

* 1x **ESP32**
* 2x **Sensores Ultrassônicos HC-SR04**
* Protoboard e jumpers
* Conexão Wi-Fi
* Um **servidor local** (Node.js, Python Flask ou similar) para receber e exibir os dados

---

## 🚀 Instruções de Uso

1. Monte o circuito de acordo com o diagrama acima.
2. Carregue o código no ESP32 utilizando a **Arduino IDE** ou **Wokwi**.
3. Configure no código os dados da sua rede Wi-Fi e o **endereço do servidor**:

   ```cpp
   const char* ssid = "SEU_WIFI";
   const char* password = "SUA_SENHA";
   const char* server = "http://SEU_IP:PORTA";
   ```
4. No computador, inicie o **servidor local** (o que exibe o HTML).
5. Acesse a página HTML no navegador para visualizar o status da bola em tempo real.

---

## 🌐 Página Web

A página exibe:

* Estado atual da bola:

  * “**Bola em campo**”
  * “**Na linha**”
  * “**Fora do campo**”
* Dados de distância dos sensores.

O visual foi aprimorado para uma interface moderna e responsiva, facilitando o acompanhamento.

---

## 👥 Integrantes

* **Vítor Silva Borsato** — RM: 561805
* **João Pedro Godinho Passiani** — RM: 561602
* **Gabriel Molinari Droppa** — RM: 562082
* **Isabela de Deus** — RM: 565988

---

## 🎥 Vídeo de Demonstração

👉 [Assista ao vídeo aqui](https://youtu.be/QBNvP2MKzi4)

---

## 🧩 Simulador Wokwi

👉 [Clique aqui para testar](https://wokwi.com/projects/446099622700027905)
