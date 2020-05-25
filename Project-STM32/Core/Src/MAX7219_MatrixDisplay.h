#ifndef MAX7219_MAX7219_MATRIXDISPLAY_H
#define MAX7219_MAX7219_MATRIXDISPLAY_H

#include "stm32f4xx_hal.h"
#include <array>
#include "Letters.h"

template<std::size_t X, std::size_t Y>
class MAX7219_MatrixDisplay {

	//SIZE OF OUR LED MATRIX
    MAX7219<X * Y> &max;
	//ARRAY CONTAINING WRITTEN VALUES
    typedef std::array<uint8_t, X * Y> DigitData;
    std::array<DigitData, 8> buffer;

    uint8_t &getByte(uint8_t x, uint8_t y) {
        int digit = y % 8;
        int row = y / 8;
        int col = x / 8;
        int bytePos = col + row * X;
        return buffer[digit][bytePos];
    }

public:

    MAX7219_MatrixDisplay(MAX7219<X * Y> &max)
            : max(max) {
    }
	//TURNS ON OR OFF THE (x,y)PIXEL
    void writePixel(uint8_t x, uint8_t y, bool value) {
        if (value) {
            getByte(x, y) |= 1 << (x % 8);
        } else {
            getByte(x, y) &= ~(1 << (x % 8));
        }
    }
	//GETS STATE OF A PIXEL
    bool getPixel(uint8_t x, uint8_t y) {
        return static_cast<bool>(getByte(x, y) & (1 << (x % 8)));
    }
	//SAVE CHANGES TO Display's REGISTES
    void write() {
        for (uint8_t i = 0; i < 8; i++) {
            max.sendDigit(i, buffer[i]);
        }
    }
	
	//LETTERS LIB
	void writeCoolLetter(char letter)
	{
		switch (letter)
		{
		case 84:	
			for (int y = 0; y < 8; y++) {
				for (int x = 0; x < 32; x++) {
					if (x == 0)
					{
						this->writePixel(x+1, 0, 1);
						this->writePixel(x+1, 1, 1);	
						this->writePixel(x+1, 2, 1);	
						this->writePixel(x+1, 3, 1);	
						this->writePixel(x+1, 4, 1);	
						this->writePixel(x + 2, 0, 1);
						this->writePixel(x + 2, 1, 1);	
						this->writePixel(x + 2, 2, 1);	
						this->writePixel(x + 2, 3, 1);	
						this->writePixel(x + 2, 4, 1);
						
						for (int i = 0; i < 7; i++)
						{
							this->writePixel(31, i, 0);
							this->writePixel(30, i, 0);
							this->writePixel(29, i, 0);
						}

						
						HAL_Delay(30);
						this->write();
					}
					else
					{
						this->writePixel(x - 1, 0, 0);
						this->writePixel(x - 1, 1, 0);	
						this->writePixel(x - 1, 2, 0);	
						this->writePixel(x - 1, 3, 0);	
						this->writePixel(x - 1, 4, 0);
						this->writePixel(x - 2, 0, 0);
						this->writePixel(x - 2, 1, 0);	
						this->writePixel(x - 2, 2, 0);	
						this->writePixel(x - 2, 3, 0);	
						this->writePixel(x - 2, 4, 0);
						this->writePixel(x - 3, 5, 0);	
						this->writePixel(x - 3, 6, 0);
						
						this->writePixel(x+1, 0, 1);
						this->writePixel(x+1, 1, 1);	
						this->writePixel(x+1, 2, 1);	
						this->writePixel(x+1, 3, 1);	
						this->writePixel(x+1, 4, 1);
						this->writePixel(x + 1, 5, 1);	
						this->writePixel(x + 1, 6, 1);
						this->writePixel(x + 2, 5, 1);	
						this->writePixel(x + 2, 6, 1);	
						this->writePixel(x + 3, 5, 1);	
						this->writePixel(x + 3, 6, 1);	

						
						for (int i =0;i<32;i++)
							this->writePixel(i, 7, 0);
						
						HAL_Delay(30);
						this->write();
					}
					
				}
			}
			
			break;
			
		}
	}
	//CLEAN THE MATRIX
	void clear()
	{
		for (int x = 0; x < 32; x++)
		{
			for (int y = 0; y<8;y++)
				this->writePixel(x, y, 0);
		}
		this->write();
	}
	//TURN ALL PIXELS ON
	void fill()
	{
		for (int x = 0; x < 32; x++)
		{
			for (int y = 0; y < 8; y++)
				this->writePixel(x, y, 1);
		}
		this->write();
	}
	
	//DISPLAY A STRING ON THE MATRIX
	void writeString(std::string str)
	{
		if (str == "_RES")
		{
			max.powerOff();
			max.powerOn();
			max.intensity(5);
			max.scanLimit(7);
			this->fill();
		}
		else if (str == "_CLN")
		{
			this->clear();
		}
		else
		{
			Letters let;
			for (int i = 0; i < str.length(); i++)
			{
				switch ((int)str[i])
				{
				case 43://+	
					for (std::vector<std::pair<int, int>>::iterator it = let.PLUS.begin(); it != let.PLUS.end(); ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 47:// /
					for (std::vector<std::pair<int, int>>::iterator it = let.SLASH.begin(); it != let.SLASH.end(); ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 65://A	
					for (std::vector<std::pair<int, int>>::iterator it = let.A.begin(); it != let.A.end(); ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 66://B
					for (std::vector<std::pair<int, int>>::iterator it = let.B.begin(); it != let.B.end(); ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 67://C
					for (std::vector<std::pair<int, int>>::iterator it = let.C.begin(); it != let.C.end(); ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 68: //D
					for(std::vector<std::pair<int, int>>::iterator it = let.D.begin() ; it != let.D.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 69: //E
					for(std::vector<std::pair<int, int>>::iterator it = let.E.begin() ; it != let.E.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 70: //F
					for(std::vector<std::pair<int, int>>::iterator it = let.F.begin() ; it != let.F.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 71: //G
						for(std::vector<std::pair<int, int>>::iterator it = let.G.begin() ; it != let.G.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 72: //H
						for(std::vector<std::pair<int, int>>::iterator it = let.H.begin() ; it != let.H.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 73: //I
						for(std::vector<std::pair<int, int>>::iterator it = let.I.begin() ; it != let.I.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();	
					}
					break;
				case 74: //J
						for(std::vector<std::pair<int, int>>::iterator it = let.J.begin() ; it != let.J.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 75: //K
						for(std::vector<std::pair<int, int>>::iterator it = let.K.begin() ; it != let.K.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 76: //L
					for(std::vector<std::pair<int, int>>::iterator it = let.L.begin() ; it != let.L.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 77: //M
					for(std::vector<std::pair<int, int>>::iterator it = let.M.begin() ; it != let.M.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 78: //N
					for(std::vector<std::pair<int, int>>::iterator it = let.N.begin() ; it != let.N.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 79: //O
					for(std::vector<std::pair<int, int>>::iterator it = let.O.begin() ; it != let.O.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 80: //P
					for(std::vector<std::pair<int, int>>::iterator it = let.P.begin() ; it != let.P.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 82: //R
					for(std::vector<std::pair<int, int>>::iterator it = let.R.begin() ; it != let.R.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 83: //S
					for(std::vector<std::pair<int, int>>::iterator it = let.S.begin() ; it != let.S.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 84: //T
					for(std::vector<std::pair<int, int>>::iterator it = let.T.begin() ; it != let.T.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 85: //U
					for(std::vector<std::pair<int, int>>::iterator it = let.U.begin() ; it != let.U.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 86: //V
					for(std::vector<std::pair<int, int>>::iterator it = let.V.begin() ; it != let.V.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 87: //W
					for(std::vector<std::pair<int, int>>::iterator it = let.W.begin() ; it != let.W.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 88: //X
					for(std::vector<std::pair<int, int>>::iterator it = let.X.begin() ; it != let.X.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 89: //Y
					for(std::vector<std::pair<int, int>>::iterator it = let.Y.begin() ; it != let.Y.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 90: //Z
					for(std::vector<std::pair<int, int>>::iterator it = let.Z.begin() ; it != let.Z.end() ; ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
				case 95://_
					for (std::vector<std::pair<int, int>>::iterator it = let.DASH.begin(); it != let.DASH.end(); ++it) {
						this->writePixel(it->first + (i * 8), it->second, 1);
						this->write();
					}
					break;
			
				case 32://SPACE
				default:
					for (int x = i * 8; x < i * 8 + 8; x++)
					{
						for (int y = 0; y < 8; y++)
							this->writePixel(x, y, 0);
					}
					break;
				}
			}
		}
		

	}

};


#endif //MAX7219_MAX7219_MATRIXDISPLAY_H