//Creating and connecting STOMP client for communication through websocket
const socket = new SockJS("/silo-websocket")
const stompClient = Stomp.over(socket);

//Subscribing to three topics,
//linking each to method to be executed
//when a message is received
const onConnect = () => {
    stompClient.subscribe("/topic/temperatures/update", onReceivedTempMessage);
    stompClient.subscribe("/topic/humidity/update", onReceivedHumMessage);
    stompClient.subscribe("/topic/distances/update", onReceivedDistMessage);
    stompClient.subscribe("/topic/notification", onReceivedNotifMessage);
}

const onError = () => {
    console.log("Could not establish WebSocket connection");
}


stompClient.connect({}, onConnect, onError);

const onReceivedTempMessage = (payload) => {
    const payloadBody = JSON.parse(payload.body);

    //Updating card
    const card = document.getElementById("temp-elem");
    card.textContent = payloadBody.tvalue;
}

const onReceivedHumMessage = (payload) => {
    const payloadBody = JSON.parse(payload.body);

    //Updating card
    const card = document.getElementById("humid-elem");
    card.textContent = payloadBody.hvalue;
}

const onReceivedDistMessage = (payload) => {
    const payloadBody = JSON.parse(payload.body);

    //Updating card
    const card = document.getElementById("grain-elem");
    card.textContent = payloadBody.percentage;
}

const onReceivedNotifMessage = (payload) => {
    const popup = document.getElementById("siloFullPopup");
    const warningBlock = document.getElementById("fullWarning");
    if (payload.body == "true"){
        popup.classList.add("show");

        const popupMessage = document.getElementById("popupMessage");
        
        popupMessage.textContent = "Warning! Silo is soon full. Please organize pickup.";

        const warningBlock = document.getElementById("fullWarning");
        warningBlock.classList.add("show");

        const card = document.getElementById("grain-elem");
        
    } else {
        popup.classList.remove("show");
        warningBlock.classList.remove("show");
    }
}

const configureClosePopup = () => {
    const closePopupButton = document.getElementById("closePopup");
    const popup = document.getElementById("siloFullPopup");

    closePopupButton.addEventListener(
        "click",
        function () {
            popup.classList.remove("show");
        }
    );
}

document.addEventListener("DOMContentLoaded", function() { 
    configureClosePopup();
});