import qualified System.Serial as SS
import System.IO
import Network.HTTP.Simple
import Data.Time.Clock
import Control.Concurrent
import Data.Word (Word8)
import Foreign.Marshal.Array (newArray)

import Pollution
import Weather

openSerial :: IO Handle
openSerial = do
  commHandle <- SS.openSerial "/dev/ttyACM0" SS.B9600 8 SS.One SS.NoParity SS.NoFlowControl
  threadDelay 4000000
  return commHandle

writeSerial :: Handle -> [Word8] -> IO ()
writeSerial h buf = do
  p <- newArray buf
  hPutBuf h p (length buf)
  putStrLn ("Wrote bytes: " ++ show buf)

main :: IO ()
main = do
  commHandle <- openSerial
  --commHandle <- snd <$> openBinaryTempFileWithDefaultPermissions "/tmp" "atmega-meteo"

  today <- utctDay <$> getCurrentTime
  pollution <- currentMeasurements . getResponseBody <$> fetchPollution today
  print pollution

  pm25 <- return . round . snd $ pollution !! 1
  pm10 <- return . round . snd $ head pollution

  buf <- return [0x20, pm25, pm10]
  writeSerial commHandle buf

  Just (temp, humid) <- getWeather
  print (temp, humid)

  buf <- return [0x21, round temp, round humid]
  writeSerial commHandle buf

  hClose commHandle
