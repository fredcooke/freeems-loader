/*
 * FreeEMS_LoaderComms.h
 *
 *  Created on: Oct 29, 2010
 *      Author: seank
 */

#ifndef FREEEMS_LOADERCOMMS_H_
#define FREEEMS_LOADERCOMMS_H_

#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
//#include <QSerialPort>
//#include <qextserialport.h>
#include <QString>
#include <QThread>
#include <QObject>
#include <QDebug>
//#include <QMutex>
#include "FreeEMS_SerialPort.h"
//#include <QTimer>

#include "FreeEMS_LoaderSREC.h"

#include <QObject>

#define SM_READY_CHAR_SIZE      0x03
#define ONE_TWENTY_EIGHT_K_RECORDS     128000  //enough records to hold 4MB at 16bytes each
using namespace std;

/**
 * Thrown if timeout occurs
 */
class timeout_exception : public std::runtime_error

{
public:
  timeout_exception(const std::string& arg) :
    runtime_error(arg)
  {
  }
  // timeout_exception(const std::string& arg)  std::cout<<arg {}
};

/**
 * Serial port class, with timeout on read operations.
 */
class FreeEMS_LoaderComms : public QThread //public QObject
{
Q_OBJECT
public:
  FreeEMS_LoaderComms();
  /**
   * Opens a serial device. By default timeout is disabled.
   * serial device
   */

  /*
   *  B7/DC/IDID — Returns the constant $DC (Device C=12) and the 2-byte
   *  HCS12 device ID register. Please refer to selected device guides for device ID
   *  register contents.
   */
  void
  ripDevice();

  void openTest(QString serPortName);

  void
  loadDevice();

  void
  init();

  void
  clearSets();

  void
  generateRecords(vector<string> lineArray);

  bool
  lineIsLoadable(string* line);

  void
  setThreadAction(int action);

  void
  setRipFilename(QString name);

  void
  setLoadFilename(QString name);

  void
  resetSM();

  int
  getDeviceByteCount();

  void
  loadRecordSet();

  void
  SMWriteByteBlock(unsigned int address, char* bytes, int numBytes);

  //void SMSetLoadAddress(unsigned int address, unsigned int typeID, int numBytes);

  /*
   *  B7/DC/IDID — Returns the constant $DC (Device C=12) and the 2-byte
   *  HCS12 device ID register. Please refer to selected device guides for device ID
   *  register contents.
   */
  void
  returnFlashType(char *responce);

  void
  setFlashType(const char *commonName);

  void
  SMSetPPage(char PPage);

  void
  SMReadByteBlock(unsigned int address, char plusBytes, std::vector<char> &vec);

  void
  SMReadChars(const char *data, size_t size);

  void
  flushRXStream();

  /*
   * Read a block of memory starting at address specified.
   * Block is read twice to check integrity.
   * 256 bytes max
   */

  int
  verifyReturn();

  //bool
  //verifyReturn(std::vector<char> &vec);

  /**
   * Opens a serial device.
   */
  void open(QString serPortName, unsigned int baud_rate);

  /**
   * \return true if serial device is open
   */
  bool
  isReady() const;
  /**
   * \return true if serial device is open
   */
  bool
  isOpen() const;

  /**
   * Close the serial device
   * \throws boost::system::system_error if any error
   */
  void
  close();

  /**
   * Set the timeout on read/write operations.
   * To disable the timeout, call setTimeout(boost::posix_time::seconds(0));
   */
//  void
//  setTimeout(const boost::posix_time::time_duration& t); //TODO reimpliment

  /**
   * Write data
   * \param data array of char to be sent through the serial device
   * \param size array size
   * \throws boost::system::system_error if any error
   */
  void
  write(const char *data, size_t size);

  /**
   * Write data
   * \param data to be sent through the serial device
   * \throws boost::system::system_error if any error
   */
  void
  write(const std::vector<char>& data);

  void
  write(const char *data);

  /**
   * Write a string. Can be used to send ASCII data to the serial device.
   * To send binary data, use write()
   * \param s string to send
   * \throws boost::system::system_error if any error
   */
  void
  writeString(const std::string& s);

  void test();
  /**
   * Read some data, blocking
   * \param data array of char to be read through the serial device
   * \param size array size
   * \return numbr of character actually read 0<=return<=size
   * \throws boost::system::system_error if any error
   * \throws timeout_exception in case of timeout
   */
  void
  read(char *data, size_t size);

  void
  read(unsigned char *data, size_t size);
  /**
   * Read some data, blocking
   * \param size how much data to read
   * \return the receive buffer. It iempty if no data is available
   * \throws boost::system::system_error if any error
   * \throws timeout_exception in case of timeout
   */
  std::vector<char>
  read(size_t size);

  /**
   * Read a string, blocking
   * Can only be used if the user is sure that the serial device will not
   * send binary data. For binary data read, use read()
   * The returned string is empty if no data has arrived
   * \param size hw much data to read
   * \return a string with the received data.
   * \throws boost::system::system_error if any error
   * \throws timeout_exception in case of timeout
   */
  std::string
  readString(size_t size);

  /**
   * Read a line, blocking
   * Can only be used if the user is sure that the serial device will not
   * send binary data. For binary data read, use read()
   * The returned string is empty if the line delimiter has not yet arrived.
   * \param delimiter line delimiter, default="\n"
   * \return a string with the received data. The delimiter is removed from
   * the string.
   * \throws boost::system::system_error if any error
   * \throws timeout_exception in case of timeout
   */
  std::string
  readStringUntil(const std::string& delim = "\n");

  void
  erasePage(char PPage);

  void
  eraseDevice();

  void
  setSM();

  void
  setAction(int action);

  void
  run();

  bool verifyLastWrite;
  bool verifyACKs;

~FreeEMS_LoaderComms();

signals:
  void
  WOInfo(string text);
  void
  udProgress(int percent);
  void
  configureProgress(int min, int max);

private:

  // TNX STUFF
  //TNX::QSerialPort *serPort;
  //TNX::QSerialPort *serPorttest;
  //TNX::QPortSettings *serPortSettings;

  FreeEMS_SerialPort *serPort;


  /**
   * Parameters of performReadSetup.
   * Just wrapper class, no encapsulation provided
   */
//  class ReadSetupParameters
//  {
//  public:
//    ReadSetupParameters() :
//      fixedSize(false), delim(""), data(0), size(0)
//    {
//    }
//
//    explicit
//    ReadSetupParameters(const std::string& delim) :
//      fixedSize(false), delim(delim), data(0), size(0)
//    {
//    }
//
//    ReadSetupParameters(char *data, size_t size) :
//      fixedSize(true), delim(""), data(data), size(size)
//    {
//    }
//
//    //Using default copy constructor, operator=
//
//    bool fixedSize; ///< True if need to read a fixed number of parameters
//    std::string delim; ///< String end delimiter (valid if fixedSize=false)
//    char *data; ///< Pointer to data array (valid if fixedSize=true)
//    size_t size; ///< Array size (valid if fixedSize=true)
//  };

  /**
   * This member function sets up a read operation, both reading a specified
   * number of characters and reading until a delimiter string.
   */
//  void
//  performReadSetup(const ReadSetupParameters& param);

  /**
   * Callack called either when the read timeout is expired or canceled.
   * If called because timeout expired, sets result to resultTimeoutExpired
   */
//  void
//  timeoutExpired(const boost::system::error_code& error); //TODO reimpliment

  /**
   * Callback called either if a read complete or read error occurs
   * If called because of read complete, sets result to resultSuccess
   * If called because read error, sets result to resultError
   */
//  void
//  readCompleted(const boost::system::error_code& error,
//      const size_t bytesTransferred);

  /**
   * Possible outcome of a read. Set by callbacks, read from main code
   */
  enum ReadResult
  {
    resultInProgress, resultSuccess, resultError, resultTimeoutExpired
  };
  enum ReadResult result; ///< Used by read with timeout
  size_t bytesTransferred; ///< Used by async read callback
//  ReadSetupParameters setupParameters; ///< Global because used in the OSX fix

  FreeEMS_LoaderSREC *s19SetOne;
  FreeEMS_LoaderSREC *s19SetTwo;

  int s19SetOneCount;
  int s19SetTwoCount;
  unsigned int lastLoadAddress;

  QString ripFilename;
  QString loadFilename;

  int flashTypeIndex;
  int threadAction;
  bool fDeviceIsSet;
  bool smIsReady;
  bool flushMode;
};

#endif /* FREEEMS_LOADERCOMMS_H_ */
