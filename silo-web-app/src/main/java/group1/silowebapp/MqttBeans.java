package group1.silowebapp;

import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.integration.annotation.ServiceActivator;
import org.springframework.integration.channel.DirectChannel;
import org.springframework.integration.core.GenericHandler;
import org.springframework.integration.core.MessageProducer;
import org.springframework.integration.dsl.IntegrationFlow;
import org.springframework.integration.mqtt.core.DefaultMqttPahoClientFactory;
import org.springframework.integration.mqtt.core.MqttPahoClientFactory;
import org.springframework.integration.mqtt.inbound.MqttPahoMessageDrivenChannelAdapter;
import org.springframework.integration.mqtt.support.DefaultPahoMessageConverter;
import org.springframework.integration.mqtt.support.MqttHeaders;
import org.springframework.messaging.Message;
import org.springframework.messaging.MessageChannel;
import org.springframework.messaging.MessageHandler;
import org.springframework.messaging.MessagingException;

@Configuration
public class MqttBeans {
    
    @Bean
    public MqttPahoClientFactory mqttClientFactory(){
        DefaultMqttPahoClientFactory factory = new DefaultMqttPahoClientFactory();
        MqttConnectOptions options = new MqttConnectOptions();
        options.setServerURIs(new String[] {"tcp://broker.mqtt-dashboard.com:1883"});
        options.setCleanSession(true);
        factory.setConnectionOptions(options);

        return factory;
    }

    @Bean
    public MessageChannel mqttInputChannel(){
        return new DirectChannel();
    }

    @Bean
    IntegrationFlow inboundFlow(MqttPahoMessageDrivenChannelAdapter inboundAdapter) {
        return IntegrationFlow
                .from(inboundAdapter)
                .handle((GenericHandler<String>) (payload, headers) -> {
                    System.out.println("new message: " + payload);
                    headers.forEach((k, v) -> System.out.println(k + "=" + v));
                    return null;
                })
                .get();
    }

    @Bean
    MqttPahoMessageDrivenChannelAdapter inboundAdapter(
            MqttPahoClientFactory clientFactory, @Value("wio/information") String topic) {
        return new MqttPahoMessageDrivenChannelAdapter("consumer", clientFactory, topic);
    }

    //@Bean
    //public MessageProducer inbound(){
    //    MqttPahoMessageDrivenChannelAdapter adapter = new MqttPahoMessageDrivenChannelAdapter(
    //        "serverIn", mqttClientFactory(),"#");
    //    adapter.setCompletionTimeout(5000);
    //    adapter.setConverter(new DefaultPahoMessageConverter());
    //    adapter.setQos(2);
    //    adapter.setOutputChannel(mqttInputChannel());
    //    return adapter;
    //}
//
    //@Bean
    //@ServiceActivator(inputChannel = "mqttInputChannel")
    //public MessageHandler handler(){
    //    return new MessageHandler(){
//
    //        @Override
    //        public void handleMessage(Message<?> message) throws MessagingException{
    //            String topic = message.getHeaders().get(MqttHeaders.RECEIVED_TOPIC).toString();
    //            if (topic.equals("myTopic")){
    //                System.out.println("This is our topic!");
    //            }
    //            System.out.println(message.getPayload());
    //        }
    //    };
    //}
}
