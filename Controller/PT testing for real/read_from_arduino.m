% ser = serialport("COM3", 115200);

while 1
    % send signal to arduino to read sensor
    write(ser, 49, "char")
    % wait for response
    while ser.NumBytesAvailable == 0
    end
    pause(.01);
    % read in data from arduino
    raw_pressure = str2double(readline(ser));
    fprintf("%d\n", raw_pressure);
    pause(.1)
end