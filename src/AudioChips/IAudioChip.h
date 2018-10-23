#ifndef IAudioChip_H
#define IAudioChip_H

class IAudioChip
{
	virtual void reset() = 0;
	virtual void write (uint8_t data) {}
	virtual void write (uint8_t reg, uint8_t data) {}
	virtual void write (uint8_t reg, uint8_t data, uint8_t port=0) {}
};
#endif // IAudioChip_H