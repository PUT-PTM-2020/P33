<h4>Weather Station </h4>
Weather Station is a project for unviersity where the main goal is usage of STM32 microcontroler.</br>
It works with mobile app and rest api created for this project. Communication is based on a remote server which serves endpoints to post data and to get data from microcontorler and into mobile app.</br>
All implementation are inside this repository:
<li>Mobile App - created using Android Studio</li>
<li>Project-STM32 - created using STM32CubeIDE</li>
<li>Rest API - created using Spring library and IntelliJ IDEA</li>

<h4>Used components</h4>
<li>STM32F4DISCOVERY</li>
<li>BME280 - temterature/humidity/pressure sensor</li>
<li>ESP8266 - wireless comunication</li>
<li>MAX7219 - LED display (8 cascaded matrices)</li>
<li>UART <-> USB converter - debbuging connection on ESP8266 </li>

<h4>Wiring</h4>
<li>BME280</li>
<table>
    <tr>
        <th>STM32</th>
        <th>BME280</th>
    </tr>
    <tr>
        <td>PB6</td>
        <td>SCL</td>
    </tr>
    <tr>
        <td>PB7</td>
        <td>SDA</td>
    <tr>
</table>
<li>ESP8266</li>
<table>
    <tr>
        <th>STM32</th>
        <th>ESP8266</th>
    </tr>
    <tr>
        <td>PC11</td>
        <td>TXD</td>
    </tr>
    <tr>
        <td>PC10</td>
        <td>RXD</td>
    <tr>
</table>
<li>MAX7219</li>
<table>
    <tr>
        <th>STM32</th>
        <th>MAX7219</th>
    </tr>
    <tr>
        <td>PA7</td>
        <td>DIN</td>
    </tr>
    <tr>
        <td>PA5</td>
        <td>CLK</td>
    <tr>
    <tr>
        <td>PA4</td>
        <td>CS</td>
    <tr>
</table>
<li>UART for debugging</li>
<table>
    <tr>
        <th>STM32</th>
        <th>UART</th>
    </tr>
    <tr>
        <td>PA3</td>
        <td>TX</td>
    </tr>
    <tr>
        <td>PA2</td>
        <td>RX</td>
    <tr>
</table>

<h4>Contributors</h4>
<li><a href="https://github.com/96peterharris">96peterharris</a></li>
<li><a href="https://github.com/CatOnXTC">karol.sienkiewicz</a></li>
<li><a href="https://github.com/Niewidzialny84">Niewidzialny84</a></li>