#include "Huffman.h"

/*
 * АЛГОРИТМ СЖАТИЯ ДАННЫХ ХАФФМАНА
 * 
 * Напишите две функции для создания архива из одного файла и извлечения файла из архива.
 * 
 * // Метод архивирует данные из потока original
 * void Encode(IInputStream& original, IOutputStream& compressed);
 * 
 * // Метод восстанавливает оригинальные данные
 * void Decode(IInputStream& compressed, IOutputStream& original);
 * 
 * где:
 * typedef char byte;
 * interface IInputStream {
 *     // Возвращает false, если поток закончился
 *     virtual bool Read(byte& value) = 0;
 * };
 * 
 * interface IOutputStream {
 *     virtual void Write(byte value) = 0;
 * };
 * 
 * В архиве сохраняйте дерево Хаффмана и код Хаффмана от исходных данных.
 * Дерево Хаффмана требуется хранить эффективно - не более 10 бит на каждый 8-битный
 * символ.
 * В контест необходимо отправить .cpp файл содержащий функции Encode, Decode, а
 * также включающий файл Huffman.h. Тестирующая программа выводит размер сжатого
 * файла в процентах от исходного.
 */

class bitIStream {
  public:
    bitIStream( IInputStream& stream ) :
        ostream( stream ), bits( 8 ), buffer( 0 ) {};
    bool readBit( bool& bit );
    bool readByte( byte& byte );

  private:
    IOutputStream& ostream;
    unsigned char bits;
    unsigned char buffer;
};

class bitOStream {
  public:
    bitOStream( IInputStream& stream );
        istream( stream ), bits( 8 ), buffer( 0 ) {};
    bool writeBit( bool bit );
    bool writeByte( byte byte );

  private:
    IInputStream& istream;
    unsigned char bits;
    unsigned char buffer;
};

class bitStream : public bitIStream, bitOStream {
    bitStream( IInputStream& istream, IOutputStream& ostream ) :
        bitIStream( istream ), bitOStream( ostream ) {};
};

template <class T>
class HaffmanTree<T> {
  public:
  private:
    struct node {
        node* left;
        node* right;
        T value;
    };
};

void Encode(IInputStream& original, IOutputStream& compressed)
{
    
}

void Decode(IInputStream& compressed, IOutputStream& original)
{
    
}

bool bitIStream::readBit( bool& bit )
{
    assert( bits <= 8 );

    if( bits == 8 ) {
        if( !istream.Read( buffer ) ) {
            return false;
        }
        bits = 0;
    }

    bits++;
    bit = ( (buffer >> (8 - bits) ) & 1 ) != 0;
    return true;
}

bool bitIStream::readByte( byte& byte )
{
    assert( bits <= 8 );
    assert( bits > 0 );

    if( bits == 8 ) {
       return stream.Read( byte );
    }

    const byte upper = byte << bits;
    if( !stream.Read( byte ) ) {
        return false;
    }
    const int lower = size
