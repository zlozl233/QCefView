(self.webpackChunkqcefviewdoc=self.webpackChunkqcefviewdoc||[]).push([[195],{3669:function(e,t,n){"use strict";n.r(t),n.d(t,{default:function(){return w}});var r=n(7294),a=n(6010),i=n(7019),o=n(9960),l=n(2263),s=n(5999),u="heroBanner_etFc",c="indexRow_jKma",d="carousel_40bO",f="buttons_+YzY",p=n(7462),m="featuresSec_Suzp",E="featureSvg_d3xR",O=[{Svg:"img/easy-to-use.svg",title:r.createElement(s.Z,{id:"index.FeatureList.easyToUseTitle"},"Easy to Use"),description:r.createElement(s.Z,{id:"index.FeatureList.easyToUseDesc"},"QCefView was designed from the ground up to be easily used to leverage the powerful capabilities of lib CEF with Qt framework.")},{Svg:"img/cross-platform-support.svg",title:r.createElement(s.Z,{id:"index.FeatureList.crossPlatformTitle"},"Cross-Platform Support"),description:r.createElement(s.Z,{id:"index.FeatureList.crossPlatformDesc"},"QCefView was also implemented as a cross-platform component which works perfectly on Windows, macOS and Linux.")},{Svg:"img/powered-by-qt.svg",title:r.createElement(s.Z,{id:"index.FeatureList.poweredByQtTitle"},"Powered by Qt & CEF"),description:r.createElement(s.Z,{id:"index.FeatureList.poweredByQtDesc"},"QCefView encapsulated the lib CEF without CEF stuff exposed.Use QCefView like any other widgets in Qt framework to build hybrid application.")}];function _(e){var t=e.Svg,n=e.title,i=e.description;return r.createElement("div",{className:(0,a.Z)("col col--4")},r.createElement("div",{className:"text--center"},r.createElement("img",{src:t,className:E,alt:n})),r.createElement("div",{className:"text--center padding-horiz--md"},r.createElement("h3",null,n),r.createElement("p",null,i)))}function N(){return r.createElement("div",{className:m},r.createElement("div",{className:"container"},r.createElement("div",{className:"row"},O.map((function(e,t){return r.createElement(_,(0,p.Z)({key:t},e))})))))}var I="carouselBox_uOU2",v="cardItem_tFfN",y="cardImage_w1Ae",T=n(5910),b=n.n(T),h=[{img:"img/windows-demo.png"},{img:"img/macOS-demo.png"},{img:"img/linux-demo.png"}];function g(e){var t=e.img;return r.createElement("div",{className:v},r.createElement("img",{src:t,className:y}))}function x(){return r.createElement("div",{className:I},r.createElement(b(),{autoplay:!0,spread:"wide",autoplay_speed:5e3},h.map((function(e,t){return r.createElement(g,(0,p.Z)({key:t},e))}))))}function S(){var e=(0,l.Z)().siteConfig;return r.createElement("header",{className:(0,a.Z)("hero hero--primary",u)},r.createElement("div",{className:"container"},r.createElement("div",{className:(0,a.Z)("row",c)},r.createElement("div",{className:"col"},r.createElement("h1",{className:"hero__title"},e.title),r.createElement("p",{className:"hero__subtitle"},r.createElement(s.Z,{id:"index.tagLine"},"A QWidget-based Web View Component Integrated with CEF")),r.createElement("div",{className:f},r.createElement(o.Z,{className:"button button--secondary button--lg",to:"/docs/intros"},r.createElement(s.Z,{id:"index.ButtonText.getStated",description:"The text for button on index center"},"Get Started"))))),r.createElement("div",{className:(0,a.Z)("row",c)},r.createElement("div",{className:"col"},r.createElement("div",{className:d},r.createElement(x,null))))))}function w(){var e=(0,l.Z)().siteConfig;return r.createElement(i.Z,{title:""+e.title,description:""},r.createElement(S,null),r.createElement("main",null,r.createElement(N,null)))}},5910:function(e,t,n){e.exports=function(e){var t={};function n(r){if(t[r])return t[r].exports;var a=t[r]={i:r,l:!1,exports:{}};return e[r].call(a.exports,a,a.exports,n),a.l=!0,a.exports}return n.m=e,n.c=t,n.d=function(e,t,r){n.o(e,t)||Object.defineProperty(e,t,{enumerable:!0,get:r})},n.r=function(e){"undefined"!=typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(e,Symbol.toStringTag,{value:"Module"}),Object.defineProperty(e,"__esModule",{value:!0})},n.t=function(e,t){if(1&t&&(e=n(e)),8&t)return e;if(4&t&&"object"==typeof e&&e&&e.__esModule)return e;var r=Object.create(null);if(n.r(r),Object.defineProperty(r,"default",{enumerable:!0,value:e}),2&t&&"string"!=typeof e)for(var a in e)n.d(r,a,function(t){return e[t]}.bind(null,a));return r},n.n=function(e){var t=e&&e.__esModule?function(){return e.default}:function(){return e};return n.d(t,"a",t),t},n.o=function(e,t){return Object.prototype.hasOwnProperty.call(e,t)},n.p="",n(n.s=1)}([function(e,t,n){"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.POSITION={PREV:"prev",NEXT:"next",CURRENT:"current",HIDDEN:"hidden"},t.ALIGNMENT={HORIZONTAL:"horizontal",VERTICAL:"vertical"},t.SPREAD={NARROW:"narrow",MEDIUM:"medium",WIDE:"wide"}},function(e,t,n){"use strict";Object.defineProperty(t,"__esModule",{value:!0});var r=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e},a=function(){function e(e,t){for(var n=0;n<t.length;n++){var r=t[n];r.enumerable=r.enumerable||!1,r.configurable=!0,"value"in r&&(r.writable=!0),Object.defineProperty(e,r.key,r)}}return function(t,n,r){return n&&e(t.prototype,n),r&&e(t,r),t}}(),i=n(2),o=c(i),l=c(n(3)),s=n(6),u=n(0);function c(e){return e&&e.__esModule?e:{default:e}}var d=function(e){function t(e){!function(e,t){if(!(e instanceof t))throw new TypeError("Cannot call a class as a function")}(this,t);var n=function(e,t){if(!e)throw new ReferenceError("this hasn't been initialised - super() hasn't been called");return!t||"object"!=typeof t&&"function"!=typeof t?e:t}(this,(t.__proto__||Object.getPrototypeOf(t)).call(this,e));return n.goTo=function(e){n.setState({current_index:Number(e)},n.props.afterChange)},n.next=function(){n._is_mounted&&n._cardOnClick(u.POSITION.NEXT)},n.prev=function(){return n._cardOnClick(u.POSITION.PREV)},n.getCurrentIndex=function(){return n.state.current_index},n._keydownEventListener=function(e){return 39===e.which?n.next():37===e.which?n.prev():void 0},n._autoplay=function(){if(n._is_mounted){var e=n.props.autoplay_speed,t=setInterval(n.next,e);n.setState({interval:t})}},n._resetInterval=function(){clearInterval(n.state.interval),n._autoplay()},n._getCardClass=function(e){var t=n.props.children,r=n.state.current_index;return null===r?u.POSITION.HIDDEN:e===r?u.POSITION.CURRENT:e===r+1||0===e&&r===o.default.Children.count(t)-1?u.POSITION.NEXT:e===r-1||e===o.default.Children.count(t)-1&&0===r?u.POSITION.PREV:u.POSITION.HIDDEN},n._cardOnClick=function(e){var t=n.props,r=t.children,a=t.autoplay,i=n.state.current_index;a&&n._resetInterval(),e===u.POSITION.NEXT?i===o.default.Children.count(r)-1?n.setState({current_index:0},n.props.afterChange):n.setState({current_index:i+1},n.props.afterChange):e===u.POSITION.PREV&&(0===i?n.setState({current_index:o.default.Children.count(r)-1},n.props.afterChange):n.setState({current_index:i-1},n.props.afterChange))},n.ChildComponents=function(){var e=n.props,t=e.alignment,a=e.spread,i=e.disable_box_shadow;return o.default.Children.map(n.props.children,(function(e,l){var u=n._getCardClass(l);return o.default.createElement("div",{key:l,onClick:function(){return n._cardOnClick(u)},style:r({},s.STYLES.CARD,{opacity:(0,s.getOpacity)(u),zIndex:(0,s.getZIndex)(u),transform:(0,s.getTransform)(u,t,a),boxShadow:(0,s.getBoxShadow)(u,t,i),cursor:(0,s.getCursor)(u,t)})},e)}))},n.state={current_index:e.disable_fade_in?e.initial_index:null,interval:null},n}return function(e,t){if("function"!=typeof t&&null!==t)throw new TypeError("Super expression must either be null or a function, not "+typeof t);e.prototype=Object.create(t&&t.prototype,{constructor:{value:e,enumerable:!1,writable:!0,configurable:!0}}),t&&(Object.setPrototypeOf?Object.setPrototypeOf(e,t):e.__proto__=t)}(t,e),a(t,[{key:"componentDidMount",value:function(){var e=this,t=this.props,n=t.initial_index,r=t.disable_keydown,a=t.disable_fade_in,i=t.autoplay;this._is_mounted=!0,a||setTimeout((function(){e.setState({current_index:n})}),.25),r||(document.onkeydown=this._keydownEventListener),i&&this._autoplay()}},{key:"componentWillUnmount",value:function(){this._is_mounted=!1,this.props.disable_keydown||(document.onkeydown=null)}},{key:"render",value:function(){return o.default.createElement("div",{style:s.STYLES.CONTAINER},o.default.createElement(this.ChildComponents,null))}}]),t}(i.Component);d.propTypes={alignment:l.default.oneOf([u.ALIGNMENT.HORIZONTAL,u.ALIGNMENT.VERTICAL]),spread:l.default.oneOf([u.SPREAD.NARROW,u.SPREAD.MEDIUM,u.SPREAD.WIDE]),initial_index:l.default.number,disable_keydown:l.default.bool,disable_box_shadow:l.default.bool,disable_fade_in:l.default.bool,autoplay:l.default.bool,autoplay_speed:l.default.number,afterChange:l.default.func},d.defaultProps={alignment:u.ALIGNMENT.HORIZONTAL,spread:u.SPREAD.MEDIUM,initial_index:0,disable_keydown:!1,disable_box_shadow:!1,disable_fade_in:!1,autoplay:!1,autoplay_speed:5e3,afterChange:function(){}},t.default=d},function(e,t){e.exports=n(7294)},function(e,t,n){e.exports=n(4)()},function(e,t,n){"use strict";var r=n(5);function a(){}function i(){}i.resetWarningCache=a,e.exports=function(){function e(e,t,n,a,i,o){if(o!==r){var l=new Error("Calling PropTypes validators directly is not supported by the `prop-types` package. Use PropTypes.checkPropTypes() to call them. Read more at http://fb.me/use-check-prop-types");throw l.name="Invariant Violation",l}}function t(){return e}e.isRequired=e;var n={array:e,bool:e,func:e,number:e,object:e,string:e,symbol:e,any:e,arrayOf:t,element:e,elementType:e,instanceOf:t,node:e,objectOf:t,oneOf:t,oneOfType:t,shape:t,exact:t,checkPropTypes:i,resetWarningCache:a};return n.PropTypes=n,n}},function(e,t,n){"use strict";e.exports="SECRET_DO_NOT_PASS_THIS_OR_YOU_WILL_BE_FIRED"},function(e,t,n){"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.STYLES=void 0,t.getOpacity=function(e){return e===r.POSITION.HIDDEN?0:1},t.getZIndex=function(e){return e===r.POSITION.HIDDEN?0:e===r.POSITION.CURRENT?2:1},t.getTransform=function(e,t,n){var a=function(e){var t=void 0,n=void 0;return e===r.SPREAD.MEDIUM?(t="-85%",n="-15%"):e===r.SPREAD.NARROW?(t="-75%",n="-25%"):e===r.SPREAD.WIDE&&(t="-95%",n="-5%"),{prev:t,next:n}}(n),i=a.prev,o=a.next;if(t===r.ALIGNMENT.HORIZONTAL){if(e===r.POSITION.PREV)return"translate("+i+", -50%) scale(0.82)";if(e===r.POSITION.NEXT)return"translate("+o+", -50%) scale(0.82)"}if(t===r.ALIGNMENT.VERTICAL){if(e===r.POSITION.PREV)return"translate(-50%, "+i+") scale(0.82)";if(e===r.POSITION.NEXT)return"translate(-50%, "+o+") scale(0.82)"}return e===r.POSITION.HIDDEN?"translate(-50%, -50%) scale(0.5)":"translate(-50%, -50%)"},t.getBoxShadow=function(e,t,n){if(!n&&e===r.POSITION.CURRENT){if(t===r.ALIGNMENT.HORIZONTAL)return"30px 0px 20px -20px rgba(0, 0, 0, .4), -30px 0px 20px -20px rgba(0, 0, 0, .4)";if(t===r.ALIGNMENT.VERTICAL)return"0px 30px 20px -20px rgba(0, 0, 0, .4), 0px -30px 20px -20px rgba(0, 0, 0, .4)"}return"unset"},t.getCursor=function(e,t){if(e===r.POSITION.NEXT){if(t===r.ALIGNMENT.HORIZONTAL)return"e-resize";if(t===r.ALIGNMENT.VERTICAL)return"s-resize"}if(e===r.POSITION.PREV){if(t===r.ALIGNMENT.HORIZONTAL)return"w-resize";if(t===r.ALIGNMENT.VERTICAL)return"n-resize"}return"unset"};var r=n(0);t.STYLES={CONTAINER:{positive:"relative",width:"100%",height:"100%",margin:0,padding:0},CARD:{position:"absolute",left:"50%",top:"50%",transition:"all 0.6s"}}}])}}]);