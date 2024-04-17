package group1.silowebapp.mqtt;

import org.springframework.messaging.Message;
import org.springframework.messaging.MessageHandler;
import org.springframework.messaging.MessageHeaders;
import org.springframework.messaging.MessagingException;

import group1.silowebapp.model.EntityFactory;
import group1.silowebapp.repository.GrainHeightRepository;
import group1.silowebapp.repository.HumidityRepository;
import group1.silowebapp.repository.SiloRepository;
import group1.silowebapp.repository.TemperatureRepository;

import org.springframework.beans.factory.annotation.Autowired;

public class SensorsMessageHandler implements MessageHandler {

    private String type;
    
	@Autowired
	private TemperatureRepository tempRepo;
    @Autowired
	private HumidityRepository humiRepo;
    @Autowired
	private GrainHeightRepository quantityRepo;
    @Autowired
    private SiloRepository siloRepository;

    public SensorsMessageHandler(String type){
        this.type = type; 
    }

    @Override
    public void handleMessage(Message<?> message) throws MessagingException{
        MessageHeaders headers = message.getHeaders();                  //gets meta-info about message
        headers.forEach((k, v) -> System.out.println(k + "=" + v));
		System.out.println(message.getPayload());

        String content = message.getPayload().toString();
        String[] splitContent = content.split("/");
        Double reading = Double.valueOf(splitContent[0]);
        String dateTime = splitContent[1];

        switch(type){
            case "Humidity":
                humiRepo.save(EntityFactory.createHumidity(reading, dateTime, siloRepository.findById(1L)));
                break;
            case "Temperature":
                tempRepo.save(EntityFactory.createTemperature(reading, dateTime, siloRepository.findById(1L)));
                break;
            case "GrainHeight":
                quantityRepo.save(EntityFactory.createGrainHeight(reading, dateTime, siloRepository.findById(1L)));
                break;
        }
    }
}