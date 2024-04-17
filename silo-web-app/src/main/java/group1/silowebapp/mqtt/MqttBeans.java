package group1.silowebapp.mqtt;

import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.integration.annotation.ServiceActivator;
import org.springframework.integration.channel.DirectChannel;
import org.springframework.integration.core.MessageProducer;
import org.springframework.integration.mqtt.core.DefaultMqttPahoClientFactory;
import org.springframework.integration.mqtt.core.MqttPahoClientFactory;
import org.springframework.integration.mqtt.inbound.MqttPahoMessageDrivenChannelAdapter;
import org.springframework.integration.mqtt.support.DefaultPahoMessageConverter;
import org.springframework.messaging.MessageChannel;
import org.springframework.messaging.MessageHandler;

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
	public MessageChannel temperatureInputChannel() {
		return new DirectChannel();
	}

    @Bean
    public MessageChannel distanceInputChannel() {
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
	public MessageProducer inboundDistance() {
		MqttPahoMessageDrivenChannelAdapter adapter = new MqttPahoMessageDrivenChannelAdapter("serverDistance",
				mqttClientFactory(), "wio/distance");
        setUpAdapterOptions(adapter);
		adapter.setOutputChannel(distanceInputChannel());
		return adapter;
	}

	@Bean
	@ServiceActivator(inputChannel = "temperatureInputChannel")
	public MessageHandler handlerTemperature() {
		return new SensorsMessageHandler("Temperature");
	}

    @Bean
	@ServiceActivator(inputChannel = "humidityInputChannel")
	public MessageHandler handlerHumidity() {
		return new SensorsMessageHandler("Humidity");
	}

    @Bean
	@ServiceActivator(inputChannel = "distanceInputChannel")
	public MessageHandler handlerDistance() {
		return new SensorsMessageHandler("GrainHeight");
	}
	
	private void setUpAdapterOptions(MqttPahoMessageDrivenChannelAdapter adapter){
        adapter.setCompletionTimeout(5000);
		adapter.setConverter(new DefaultPahoMessageConverter());
		adapter.setQos(2);
    }
}
