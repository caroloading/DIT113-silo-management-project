package group1.silowebapp.repository;

import group1.silowebapp.model.GrainHeight;
import org.springframework.data.repository.CrudRepository;

import java.util.List;

public interface GrainHeightRepository extends CrudRepository<GrainHeight, Long> {

    List<GrainHeight> findAllByOrderByDateTimeDesc();

    GrainHeight findTopByOrderByDateTimeDesc();
}