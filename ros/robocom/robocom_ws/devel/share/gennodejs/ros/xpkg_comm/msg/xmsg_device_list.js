// Auto-generated. Do not edit!

// (in-package xpkg_comm.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let xmsg_device = require('./xmsg_device.js');

//-----------------------------------------------------------

class xmsg_device_list {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.dev_count = null;
      this.dev_list = null;
    }
    else {
      if (initObj.hasOwnProperty('dev_count')) {
        this.dev_count = initObj.dev_count
      }
      else {
        this.dev_count = 0;
      }
      if (initObj.hasOwnProperty('dev_list')) {
        this.dev_list = initObj.dev_list
      }
      else {
        this.dev_list = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type xmsg_device_list
    // Serialize message field [dev_count]
    bufferOffset = _serializer.uint8(obj.dev_count, buffer, bufferOffset);
    // Serialize message field [dev_list]
    // Serialize the length for message field [dev_list]
    bufferOffset = _serializer.uint32(obj.dev_list.length, buffer, bufferOffset);
    obj.dev_list.forEach((val) => {
      bufferOffset = xmsg_device.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type xmsg_device_list
    let len;
    let data = new xmsg_device_list(null);
    // Deserialize message field [dev_count]
    data.dev_count = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dev_list]
    // Deserialize array length for message field [dev_list]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.dev_list = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.dev_list[i] = xmsg_device.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 4 * object.dev_list.length;
    return length + 5;
  }

  static datatype() {
    // Returns string type for a message object
    return 'xpkg_comm/xmsg_device_list';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2ceb7f0b4db86b40356e12aab2f69511';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 dev_count
    xmsg_device[] dev_list
    
    ================================================================================
    MSG: xpkg_comm/xmsg_device
    uint8 dev_class
    uint8 dev_type
    uint8 dev_number
    uint8 dev_enable
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new xmsg_device_list(null);
    if (msg.dev_count !== undefined) {
      resolved.dev_count = msg.dev_count;
    }
    else {
      resolved.dev_count = 0
    }

    if (msg.dev_list !== undefined) {
      resolved.dev_list = new Array(msg.dev_list.length);
      for (let i = 0; i < resolved.dev_list.length; ++i) {
        resolved.dev_list[i] = xmsg_device.Resolve(msg.dev_list[i]);
      }
    }
    else {
      resolved.dev_list = []
    }

    return resolved;
    }
};

module.exports = xmsg_device_list;
