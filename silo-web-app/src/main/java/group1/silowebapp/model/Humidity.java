package group1.silowebapp.model;

import jakarta.persistence.*;

@Entity
public class Humidity {

    /* Define the Object Relational Mapping (ORM). JPA/Hibernate converts
     * the definitions to the appropriate SQL DDL statements
     */
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;

    @Column(nullable = false)
    private Double hValue;

    @Column(nullable = false)
    private String dateTime;

    @ManyToOne
    @JoinColumn(name = "silo_id")
    private Silo silo;

    protected Humidity() {
    }

    public Humidity(Double hValue, String dateTime, Silo silo) {
        this.hValue = hValue;
        this.dateTime = dateTime;
        this.silo = silo;
    }

    public Long getId() {
        return id;
    }

    public Double getHValue() {
        return hValue;
    }

    public String getDateTime() {
        //Todo: format 
        return dateTime;
    }

    public Silo getSilo() {
        return silo;
    }

    public boolean isOutOfBounds(){
        if (silo != null){
            return hValue < silo.getMinHumidity() || hValue > silo.getMaxHumidity();
        } else {
            return true;
        }
        
    }

    @Override
    public String toString() {
        return String.format("Humidity[id=%d, value='%.2f', dateTime='%s']", id, hValue, dateTime);
    }
}
