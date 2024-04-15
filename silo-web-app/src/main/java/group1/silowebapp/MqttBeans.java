package group1.silowebapp;

import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
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
import org.springframework.messaging.MessageHeaders;
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

    //@Bean
    //IntegrationFlow inboundFlow(MqttPahoMessageDrivenChannelAdapter inboundAdapter) {
    //    return IntegrationFlow
    //            .from(inboundAdapter)
    //            .handle((GenericHandler<String>) (payload, headers) -> {
    //                System.out.println("new message: " + payload);
    //                headers.forEach((k, v) -> System.out.println(k + "=" + v));
    //                return null;
    //            })
    //            .get();
    //}
//
    //@Bean
    //MqttPahoMessageDrivenChannelAdapter inboundAdapter(
    //        MqttPahoClientFactory clientFactory) {
    //    return new MqttPahoMessageDrivenChannelAdapter("consumer", clientFactory, "wio/temperature", "wio/humidity", "wio/height");
    //}

    @Bean
	public MessageChannel temperatureInputChannel() {
		return new DirectChannel();
	}

    @Bean
    public MessageChannel quantityInputChannel() {
		return new DirectChannel();
	}

    @Bean
    public MessageChannel humidityInputChannel() {
		return new DirectChannel();
	}
	
	@Bean
	public MessageProducer inboundTemperature() {
		MqttPahoMessageDrivenChannelAdapter adapter = new MqttPahoMessageDrivenChannelAdapter("serverTemperature",
				mqttClientFactory(), "wio/temperature");

        setUpAdapterOptions(adapter);
		adapter.setOutputChannel(temperatureInputChannel());
		return adapter;
	}

    @Bean
	public MessageProducer inboundHumidity() {
		MqttPahoMessageDrivenChannelAdapter adapter = new MqttPahoMessageDrivenChannelAdapter("serverHumidity",
				mqttClientFactory(), "wio/humidity");

		setUpAdapterOptions(adapter);
		adapter.setOutputChannel(humidityInputChannel());
		return adapter;
	}

    @Bean
	public MessageProducer inboundQuantity() {
		MqttPahoMessageDrivenChannelAdapter adapter = new MqttPahoMessageDrivenChannelAdapter("serverQuantity",
				mqttClientFactory(), "wio/quantity");
        setUpAdapterOptions(adapter);
		adapter.setOutputChannel(quantityInputChannel());
		return adapter;
	}
	
	private void setUpAdapterOptions(MqttPahoMessageDrivenChannelAdapter adapter){
        adapter.setCompletionTimeout(5000);
		adapter.setConverter(new DefaultPahoMessageConverter());
		adapter.setQos(2);
    }

	@Bean
	@ServiceActivator(inputChannel = "temperatureInputChannel")
	public MessageHandler handlerTemperature() {
		return new MessageHandler() {

			@Override
			public void handleMessage(Message<?> message) throws MessagingException {
				MessageHeaders headers = message.getHeaders();                  //gets meta-info about message
                headers.forEach((k, v) -> System.out.println(k + "=" + v));
				System.out.println(message.getPayload());
			}

		};
	}

    @Bean
	@ServiceActivator(inputChannel = "humidityInputChannel")
	public MessageHandler handlerHumidity() {
		return new MessageHandler() {

			@Override
			public void handleMessage(Message<?> message) throws MessagingException {
				MessageHeaders headers = message.getHeaders();                  //gets meta-info about message
                headers.forEach((k, v) -> System.out.println(k + "=" + v));
				System.out.println(message.getPayload());
			}

		};
	}

    @Bean
	@ServiceActivator(inputChannel = "quantityInputChannel")
	public MessageHandler handlerQuantity() {
		return new MessageHandler() {

			@Override
			public void handleMessage(Message<?> message) throws MessagingException {
				MessageHeaders headers = message.getHeaders();                  //gets meta-info about message
                headers.forEach((k, v) -> System.out.println(k + "=" + v));
				System.out.println(message.getPayload());
			}

		};
	}
}
