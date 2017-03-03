import System.Serial
import System.IO (hPutChar, hFlush)
import Data.Char (chr)
import Network.HTTP.Simple
import Data.Time.Clock
import Data.Time.Calendar
import Control.Concurrent
import Text.XML.Light.Input (parseXML)

import Pollution
import Weather

main :: IO ()
main = do
  serial <- openSerial "/dev/ttyACM0" B9600 8 One NoParity NoFlowControl
  threadDelay 4000000
  today <- utctDay <$> getCurrentTime
  pollution <- currentMeasurements . getResponseBody <$> fetchPollution today
  putStrLn $ show pollution
  hPutChar serial $ chr 0x20
  hPutChar serial $ chr . round . snd $ pollution !! 1
  hPutChar serial $ chr . round . snd $ pollution !! 0
  Just (temp, humid) <- getWeather
  hPutChar serial $ chr 0x21
  hFlush serial
  hPutChar serial $ chr . round $ temp
  hFlush serial
  hPutChar serial $ chr . round $ humid
  hFlush serial
  putStrLn $ show (temp, humid)
