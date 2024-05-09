package group1.silowebapp.repository;

import group1.silowebapp.model.Humidity;
import org.springframework.data.repository.CrudRepository;

import java.util.List;

public interface HumidityRepository extends CrudRepository<Humidity, Long> {

    List<Humidity> findAllByOrderByDateTimeDesc();

    Humidity findTopByOrderByDateTimeDesc();
}