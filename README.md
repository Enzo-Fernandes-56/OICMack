💧 Sistema de Monitoramento de Consumo de Água via MQTT

Este projeto tem como objetivo monitorar o consumo de água utilizando um microcontrolador NodeMCU ESP8266, um sensor de fluxo YF-S201 e um LED indicativo. Os dados de vazão e volume acumulado são enviados a um broker MQTT para visualização em tempo real.

⚖️ Funcionalidades

Medição de vazão (L/min) e volume total (L) usando sensor de fluxo.

Indicação visual (LED) sempre que houver fluxo de água.

Envio dos dados para um broker MQTT em tempo real.

Reconexão automática de Wi-Fi e MQTT.

Comunicação baseada em protocolo MQTT com mensagens JSON.

⚙️ Componentes Utilizados

Componente

Descrição

NodeMCU ESP8266-12 V2

Microcontrolador com Wi-Fi integrado

Sensor YF-S201

Sensor de fluxo de água (modelo SAIER)

LED Verde

Feedback visual do fluxo

Resistores

220Ω para LED

Jumpers e Protoboard

Conexões

🔌 Esquema de Ligação

Sensor de fluxo (YF-S201): sinal → D2 (GPIO4)

LED Verde: anodo → D1 (GPIO5) (com resistor de 220Ω)

💻 Código

O código está disponível no arquivo monitoramento_agua.ino.

Principais variáveis:

fluxo → Vazão em L/min

volume_total → Volume acumulado em litros

agua/fluxo → Tópico MQTT com a vazão

agua/volume → Tópico MQTT com o volume acumulado

🌐 Comunicação MQTT

Broker público: broker.hivemq.com

Porta: 1883

Tópicos:

agua/fluxo → Publicação da vazão

agua/volume → Publicação do volume acumulado

QoS: 1 (entrega garantida ao menos uma vez)

📊 Resultados

O sistema apresentou os seguintes tempos médios de resposta:

Sensor/Atuador

Tempo Médio (ms)

Sensor de fluxo

151,25

Acionamento do LED

81,25

Envio via MQTT

325

Comentário:

Os resultados mostram que o tempo de resposta do sensor de fluxo e do LED estão dentro de uma faixa adequada para aplicações de monitoramento em tempo real. O envio MQTT apresentou maior latência, o que é esperado devido à comunicação em rede, mas ainda dentro de limites aceitáveis.



🚀 Como Usar

Instale as bibliotecas ESP8266WiFi e PubSubClient na IDE Arduino.

Configure o ssid e password da sua rede Wi-Fi no código.

Compile e envie o código para o NodeMCU.

Conecte o circuito conforme descrito.

Visualize os dados via MQTT usando um cliente (ex: MQTT Explorer).

🧠 Melhorias Futuras

Implementar interface Web para visualização local.

Adicionar sensor de nível do reservatório.

Gravar histórico em cartão SD ou banco de dados remoto.

Criar painel com gráficos usando Node-RED ou Grafana.

📚 Referências

ESP8266 Arduino Core: https://github.com/esp8266/Arduino

HiveMQ MQTT Broker: https://www.hivemq.com/

Manual Mackenzie para Trabalhos Acadêmicos: https://www.mackenzie.br/fileadmin/user_upload/Guia_Mackenzie_trabalhos_academicos_online_c_protecao.pdf
