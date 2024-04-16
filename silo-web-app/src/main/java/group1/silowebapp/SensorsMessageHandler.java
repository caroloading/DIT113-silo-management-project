package group1.silowebapp;

import org.springframework.messaging.Message;
import org.springframework.messaging.MessageHandler;
import org.springframework.messaging.MessageHeaders;
import org.springframework.messaging.MessagingException;
import org.springframework.boot.configurationprocessor.json.JSONException;
import org.springframework.boot.configurationprocessor.json.JSONObject;
import org.springframework.data.repository.CrudRepository;

public class SensorsMessageHandler<T> implements MessageHandler {

    CrudRepository<T, Long> repository;

    public SensorsMessageHandler(CrudRepository<T, Long> repo){
        this.repository = repo;
    }

    @Override
    public void handleMessage(Message<?> message) throws MessagingException{
        MessageHeaders headers = message.getHeaders();                  //gets meta-info about message
        headers.forEach((k, v) -> System.out.println(k + "=" + v));
		System.out.println(message.getPayload());

        try {
            JSONObject data = new JSONObject(message.getPayload().toString());
        } catch (JSONException ex){
            throw new RuntimeException(ex);
        }
    }


}