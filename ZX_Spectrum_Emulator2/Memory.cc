#include <fstream>
#include "Memory.h"

ROM::ROM(const char * filename)
{
	std::fstream romfile;
	romfile.open(filename, std::ios::in | std::ios::ate);
	_contents.resize(romfile.tellg());
	romfile.seekg(0);
	romfile.read(reinterpret_cast<char*>(&_contents[0]), _contents.size());
	_addr_mask = _contents.size() - 1;
}

void AddressSpace::write(unsigned address, uint8_t value, bool io)
{
		if (io == true)
			_io.write(translate_mem_addr(address), value);
		else
			_ram.write(translate_mem_addr(address), value);
//	if (io == true)
//		_io.write(address, value);//_io.write(translate_mem_addr(address), value);
//	else
//		_ram.write(address, value);
}
uint8_t AddressSpace::read(unsigned address, bool io)
{
	if (io == true)
		return _io.read(translate_mem_addr(address));//_io.write(translate_mem_addr(address));
	else {
		if (address < 32768)
			return _rom.read(translate_mem_addr(address));
		else
			return _ram.read(translate_mem_addr(address));
		}
//	if (io == true)
//		return _io.read(address);//_io.write(translate_mem_addr(address));
//	else {
//		if (address < 32768)
//			return _rom.read(address);
//		else
//			return _ram.read(address);
//	}
}
uint32_t AddressSpace::translate_mem_addr(uint16_t address)
{
	uint32_t offset = address & 0x3fff;
	uint32_t real_address = offset;
	unsigned page = (address >> 14)&0x03;
	if(page == 0){      //PZU
		if(_io.rom_page() == 0)
			real_address |= 0x20000;
		else
			real_address |= 0x24000;
	}else if(page == 1){   //video
		if (_io.vid_page() == 0)
			real_address |= 0x14000;
		else
			real_address |= 0x1c000;
	}else if(page == 2)    //ozu
		real_address |= 0x08000;
	else
		real_address |= _io.ram_page() << 14;
	return real_address;
}

/*void AddressSpace::write16(unsigned address, uint16_t value)
{
	write(address,     (value >> 0) & 0x00ff);
	write(address + 1, (value >> 8) & 0x00ff);
}

uint16_t AddressSpace::read16(unsigned address)
{
	uint16_t result = 0;
	result |= read(address);
	result |= uint16_t(read(address)) << 8;
	return result;
}*/
