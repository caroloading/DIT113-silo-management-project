var tbody = document.querySelector("tbody");
const gradient = window['chartjs-plugin-gradient'];
Chart.register(gradient);
const timeStamps = [];
const heightReadings = [];


tbody.querySelectorAll("tr").forEach(function(row){
    var heightValue = (row.querySelector("td:nth-child(2)").innerText/15)*(-100)+100;//turn grain height into to a percentage (15 is the max in this scale meaning silo is empty/0%)
    var timeValue = row.querySelector("td:nth-child(3)").innerText;

    //unshift puts the elements in the beginning of the array, thus the newest reading will be at the right-hand part of the chart.
    heightReadings.unshift(heightValue);
    timeStamps.unshift(timeValue);
});
const grainHeightChart = document.getElementById('heightChart');

new Chart(grainHeightChart,{
    type: 'bar',
    data: {
    labels: timeStamps,
        datasets: [{
        label: 'grain level',
        data: heightReadings,
        borderWidth: 0,
            gradient: {
                backgroundColor: {
                    axis: 'y',
                    colors: {
                        0: '#DAF7A6',
                        70: '#FEE08C',
                        100: '#F8AD48'
                    }
                },
                borderColor: {
                    axis: 'x',
                    colors: {

                    }
                }
            }
        }]
    },
    options: {
        scales: {
            y: {
                min: 0,
                max: 100,
            }
        }
    }
});


